// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Skill1005.h"
#include "B1Character.h"
#include "B1DebugPrint.h"

B1Skill1005::B1Skill1005(AB1Character* character)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> ResTex2dSkill(*RES_TEX2D_SKILL1005);
	if (ResTex2dSkill.Succeeded()) {
		Tex2dSkill = ResTex2dSkill.Object;
	}

	//TODO: 기획 데이터에서 가져오도록 수정
	CoolTime = 3;
	SkillStartTimestamp = 0;
	//ClassName = __CLASS__;

	Character = character;
	AnimInst = Cast<UB1AnimInstance>(Character->GetMesh()->GetAnimInstance());
}
B1Skill1005::~B1Skill1005()
{
}
void B1Skill1005::Run()
{
	if(0 == SkillStartTimestamp){
		PlayAnimation();
		SkillStartTimestamp = FDateTime::Now().ToUnixTimestamp();
	}

	Move();
}
void B1Skill1005::CheckAttack()
{

}
void B1Skill1005::Move()
{
	//TODO: 일정 거리까지만 이동하도록 수정 현재 로직은 프레임마다 이동 거리가 다를수 있다.
	FRotator Rotation = Character->GetController()->GetControlRotation();
	if (Character->GetCharacterMovement()->IsMovingOnGround() || Character->GetCharacterMovement()->IsFalling()){
		Rotation.Pitch = 0.0f;
	}
	const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
	Character->AddMovementInput(Direction, 0.8);
}
ERES_ANIM_NUM B1Skill1005::GetAnimResNum()
{
	return ERES_ANIM_NUM::_1005;
}
void B1Skill1005::PlayAnimation()
{
	AnimInst->SetSkillAnimResNum(GetAnimResNum());
}
