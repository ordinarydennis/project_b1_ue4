// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Skill1004.h"
#include "B1Character.h"

B1Skill1004::B1Skill1004()
{
}
B1Skill1004::~B1Skill1004()
{
}
void B1Skill1004::init(AB1Character* character)
{
	//TODO: ��ȹ �����Ϳ��� ���������� ����
	CoolTime = 2;
	SkillStartTimestamp = 0;
	Character = character;
	AnimationInst = Cast<UB1AnimInstance>(Character->GetMesh()->GetAnimInstance());
}
void B1Skill1004::Run()
{
	if (0 == SkillStartTimestamp) {
		PlayAnimation();
		SkillStartTimestamp = FDateTime::Now().ToUnixTimestamp();
	}
}
void B1Skill1004::CheckAttack()
{

}
ERES_ANIM_NUM B1Skill1004::GetAnimResNum()
{
	return ERES_ANIM_NUM::_1004;
}
void B1Skill1004::PlayAnimation()
{
	AnimationInst->SetSkillAnimResNum(GetAnimResNum());
}
