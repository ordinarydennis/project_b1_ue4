// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PROJECT_B1.h"
#include "GameFramework/Pawn.h"
#include "B1Monster.generated.h"

UCLASS()
class PROJECT_B1_API AB1Monster : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AB1Monster();
	void CheckAttack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstiator, AActor* DamageCauser) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	UBoxComponent* BoxCollision  = nullptr;
	
private:
	UPROPERTY(VisibleAnywhere, Category = "B1PawnComponent")
	class USkeletalMeshComponent* SkelMesh = nullptr;
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class UUserWidget> HUDWidgetClass;

};