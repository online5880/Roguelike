// Fill out your copyright notice in the Description page of Project Settings.


#include "RLCharacter.h"

#include "RLCharacterAnimInstance.h"
#include "RLPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Roguelike/Components/CombatComponent.h"
#include "MotionWarpingComponent.h"
#include "Roguelike/Components/InventoryComponent.h"

// Sets default values
ARLCharacter::ARLCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat Component"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

void ARLCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARLCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if(CombatComponent)
	{
		CombatComponent->Character = this;
		CombatComponent->AnimInstance = Cast<URLCharacterAnimInstance>(GetMesh()->GetAnimInstance());
		CombatComponent->Controller = Cast<ARLPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	}
}

void ARLCharacter::BeginPlay()
{
	Super::BeginPlay();
}


