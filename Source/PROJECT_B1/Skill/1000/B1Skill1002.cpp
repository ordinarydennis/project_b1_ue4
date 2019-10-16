// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Skill1002.h"

B1Skill1002::B1Skill1002(USkeletalMeshComponent* mesh)
{
	//��ȹ �����Ϳ��� ���������� ����
	CoolTime = 2;
	SkillStartTimestamp = 0;
	Mesh = mesh;
}

B1Skill1002::~B1Skill1002()
{
}
void B1Skill1002::Run()
{
	if (IsCoolTime()) {
		return;
	}

	SkillStartTimestamp = FDateTime::Now().ToUnixTimestamp();
	PlayAnimation();
}
ERES_ANIM_NUM B1Skill1002::GetAnimResNum()
{
	return ERES_ANIM_NUM::SingleTwoHandSword_2;
}
void B1Skill1002::PlayAnimation()
{
	AnimationInst = static_cast<UB1AnimInstance*>(Mesh->GetAnimInstance());
	AnimationInst->SetSkillAnimResNum(GetAnimResNum());
}