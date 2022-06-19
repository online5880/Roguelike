// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RLPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKE_API ARLPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	// ! 공격 - Using combat component
	void Attack();

	// ! 구르기 - Using combat component
	void Dodge();

	// ! 인벤토리
	void Inventory();

	// ! 상호작용
	void Interact();

private:

	UPROPERTY()
	TObjectPtr<class ARLCharacter> RLCharacter;

	UPROPERTY()
	TObjectPtr<class UCombatComponent> CombatComponent;

	UPROPERTY()
	TObjectPtr<class UInventoryComponent> InventoryComponent;
};
