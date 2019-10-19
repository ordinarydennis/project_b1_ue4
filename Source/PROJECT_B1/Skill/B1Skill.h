// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PROJECT_B1.h"
#include "B1AnimInstance.h"
#include "UObject/Interface.h"
#include "B1Skill.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UB1Skill : public UInterface
{
	GENERATED_BODY()

};

/**
 * 
 */
class PROJECT_B1_API IB1Skill
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Run() = 0;
protected:
	virtual ERES_ANIM_NUM GetAnimResNum() = 0;
public:
	bool IsCoolTime();

protected:
	int64 SkillStartTimestamp = 0;
	AB1Character* Character = nullptr;
	int32 CoolTime = 10;
	UB1AnimInstance* AnimationInst = nullptr;
};
