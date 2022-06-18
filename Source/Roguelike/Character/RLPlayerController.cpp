// Fill out your copyright notice in the Description page of Project Settings.


#include "RLPlayerController.h"

#include "RLCharacter.h"
#include "Roguelike/Components/CombatComponent.h"
#include "Roguelike/Components/InventoryComponent.h"

void ARLPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("MoveForward"),this,&ARLPlayerController::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"),this,&ARLPlayerController::MoveRight);
	InputComponent->BindAxis(TEXT("Turn"),this,&ARLPlayerController::Turn);
	InputComponent->BindAxis(TEXT("LookUp"),this,&ARLPlayerController::LookUp);

	InputComponent->BindAction(FName("Attack"),IE_Pressed,this,&ARLPlayerController::Attack);
	InputComponent->BindAction(FName("Dodge"),IE_Pressed,this,&ARLPlayerController::Dodge);
	InputComponent->BindAction(FName("Inventory"),IE_Pressed,this,&ARLPlayerController::Inventory);
}

void ARLPlayerController::BeginPlay()
{
	Super::BeginPlay();

	RLCharacter = Cast<ARLCharacter>(GetPawn());
}

// * Basic Movement
#pragma region Basic Movement
void ARLPlayerController::MoveForward(float Value)
{
	APawn* OwnerPawn = GetPawn();
	if(OwnerPawn != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f,OwnerPawn->GetControlRotation().Yaw,0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
		OwnerPawn->AddMovementInput(Direction,Value);
	}
}

void ARLPlayerController::MoveRight(float Value)
{
	APawn* OwnerPawn = GetPawn();
	if(OwnerPawn != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f,OwnerPawn->GetControlRotation().Yaw,0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
		OwnerPawn->AddMovementInput(Direction,Value);
	}
}

void ARLPlayerController::Turn(float Value)
{
	APawn* OwnerPawn = GetPawn();
	OwnerPawn->AddControllerYawInput(Value);
}

void ARLPlayerController::LookUp(float Value)
{
	APawn* OwnerPawn = GetPawn();
	OwnerPawn->AddControllerPitchInput(Value);
}
#pragma endregion Basic Movement

void ARLPlayerController::Attack()
{
	if(RLCharacter)
	{
		UCombatComponent* Combat = Cast<UCombatComponent>(RLCharacter->GetCombatComponent());
		{
			if(Combat)
			{
				Combat->Attack();
			}
		}
	}
}

void ARLPlayerController::Dodge()
{
	if(RLCharacter)
	{
		CombatComponent = Cast<UCombatComponent>(RLCharacter->GetCombatComponent());
		if(CombatComponent)
		{
			CombatComponent->Dodge();
		}
	}
}

void ARLPlayerController::Inventory()
{
	if(RLCharacter)
	{
		InventoryComponent = Cast<UInventoryComponent>(RLCharacter->GetInventoryComponent());
		if(InventoryComponent)
		{
			InventoryComponent->Inventory();
		}
	}
}
