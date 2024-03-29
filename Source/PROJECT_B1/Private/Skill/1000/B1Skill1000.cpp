// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Skill1000.h"
#include "B1Character.h"
#include "B1DebugPrint.h"

B1Skill1000::B1Skill1000(AB1Character* character)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> ResTex2dSkill(*RES_TEX2D_SKILL1000);
	if (ResTex2dSkill.Succeeded()) {
		Tex2dSkill = ResTex2dSkill.Object;
	}

	//TODO: 기획 데이터에서 가져오도록 수정
	CoolTime = 3;	//쿨타임이 너무 작으면 endofAnim 노티파이가 씹힐수 있다?
	SkillStartTimestamp = 0;
	//ClassName = __CLASS__;

	Character = character;
	AnimInst = Cast<UB1AnimInstance>(Character->GetMesh()->GetAnimInstance());

	Damage = 10;
}
B1Skill1000::~B1Skill1000()
{
}
void B1Skill1000::Run()
{
	if (0 == SkillStartTimestamp) {
		PlayAnimation();
		SkillStartTimestamp = FDateTime::Now().ToUnixTimestamp();
	}
}
void B1Skill1000::CheckAttack()
{
	float FinalAttackRange = 150.f;
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, Character);
	bool bResult = Character->GetWorld()->SweepSingleByChannel(
		HitResult,
		Character->GetActorLocation(),
		Character->GetActorLocation() + Character->GetActorForwardVector() * FinalAttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(50.0f),
		Params);

#if ENABLE_DRAW_DEBUG
	FVector TraceVec = Character->GetActorForwardVector() * FinalAttackRange;
	FVector Center = Character->GetActorLocation() + TraceVec * 0.5f;
	float AttackRadius = 50.f;
	float HalfHeight = FinalAttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 2.0f;

	DrawDebugCapsule(Character->GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);
#endif

	if (bResult) {
		if (HitResult.Actor.IsValid())
		{
			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(Damage, DamageEvent, Character->GetController(), Character);
		}
	}
}
ERES_ANIM_NUM B1Skill1000::GetAnimResNum()
{
	return ERES_ANIM_NUM::_1000;
}
void B1Skill1000::PlayAnimation()
{
	AnimInst->SetSkillAnimResNum(GetAnimResNum());
}