// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PROJECT_B1.h"
#include "Skill/B1Skill.h"

/**
 * 
 */
class PROJECT_B1_API B1Skill1001 : public IB1Skill
{
public:
	B1Skill1001(AB1Character* Character);
	~B1Skill1001();

public:
	virtual void Run() override;

private:
	virtual ERES_ANIM_NUM GetAnimResNum() override;

private:
	void PlayAnimation();
};
