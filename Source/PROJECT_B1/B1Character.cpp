// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Character.h"
#include "Misc/DateTime.h"

// Sets default values
AB1Character::AB1Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	SpringArm->TargetArmLength = 700.0f;
	SpringArm->SetRelativeRotation(FRotator(-70.0f, -90.0f, 0.0f));

	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bDoCollisionTest = false;
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);

	//시작 위치
	//SetActorLocation(FVector(-2560.0f, 0.0f, 0.0f), false);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("B1Character"));

	//유저가 선택한 캐릭터에따라 로딩
	//메인UI에서 입력 받은 값을 가져온다. 
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_COMMONER(
		TEXT("/Game/Resources/Market/ModularRPGHeroesPolyart/Meshes/OneMeshCharacters/CommonerSK.CommonerSK"));
	if (SK_COMMONER.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SK_COMMONER.Object);
		GetMesh()->AddLocalRotation(FRotator(0.0f, -90.0f, 0.0f));
		GetMesh()->AddRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> PLAYER_ANIM(
		TEXT("/Game/Blueprints/PlayerAnimBlueprint.PlayerAnimBlueprint_C"));
	if (PLAYER_ANIM.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(PLAYER_ANIM.Class);
	}
}
void AB1Character::RunSkill(IB1Skill* skill)
{
	Skill = skill;
}
void AB1Character::StopSkill()
{
	Skill = nullptr;
}
void AB1Character::CheckAttack()
{
	if (nullptr != Skill) {
		Skill->CheckAttack();
	}
}
// Called when the game starts or when spawned
void AB1Character::BeginPlay()
{
	Super::BeginPlay();
	
}
// Called every frame
void AB1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DirectionToMove.SizeSquared() > 0.0f) {
		GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
		AddMovementInput(DirectionToMove);
	}

	if (nullptr != Skill) {
		Skill->Run();
	}
}
void AB1Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	auto AnimationInst = Cast<UB1AnimInstance>(GetMesh()->GetAnimInstance());
	AnimationInst->OnAttackHitCheck.AddUObject(this, &AB1Character::CheckAttack);
}
float AB1Character::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//printf("Actor %s Damage %f", *GetName(), FinalDamage);
	return FinalDamage;
}
// Called to bind functionality to input
void AB1Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AB1Character::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AB1Character::LeftRight);
}
void AB1Character::UpDown(float NewAxisValue)
{
	DirectionToMove.Y = NewAxisValue * MovingSpeed;
}
void AB1Character::LeftRight(float NewAxisValue)
{
	DirectionToMove.X = NewAxisValue * MovingSpeed;
}

