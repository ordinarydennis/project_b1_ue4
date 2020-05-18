// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Monster.h"
#include "B1MonsterAnimInstance.h"

// Sets default values
AB1Monster::AB1Monster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("BoxComponent"));
    BoxCollision->SetGenerateOverlapEvents(true);
    BoxCollision->SetBoxExtent(FVector(40.f, 40.f, 100.f));
    BoxCollision->SetCollisionProfileName(TEXT("B1Monster"));

    RootComponent = BoxCollision;

    // Rendering - SkeletalMeshComponent
    SkelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("B1MonsterSM"));
    SkelMesh->SetRelativeLocationAndRotation(
        FVector(0.f, 0.f, -90.f),
        FRotator(0.f, -90.f, 0.f)    // Roll
    );

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Monster(*RES_SK_MONSTER1);
    SkelMesh->SetSkeletalMesh(SK_Monster.Object);
    // Attacth to RootComponent
    SkelMesh->SetupAttachment(BoxCollision);

    static ConstructorHelpers::FClassFinder<UAnimInstance> ResAnimInst(*RES_ANIM_INST_MONSTER);
    if (ResAnimInst.Succeeded()) {
        SkelMesh->SetAnimInstanceClass(ResAnimInst.Class);
    }
}

// Called when the game starts or when spawned
void AB1Monster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AB1Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AB1Monster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
void AB1Monster::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    auto AnimInst = Cast<UB1MonsterAnimInstance>(SkelMesh->GetAnimInstance());
    AnimInst->OnAttackHitCheck.AddUObject(this, &AB1Monster::CheckAttack);
}
float AB1Monster::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
    float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    printf("Actor %s took Damage %f", *GetName(), FinalDamage);

    auto AnimInst = Cast<UB1MonsterAnimInstance>(SkelMesh->GetAnimInstance());
    AnimInst->SetDeadAnim();

    return FinalDamage;
}
void AB1Monster::CheckAttack()
{
    printf("CheckAttack()");
}