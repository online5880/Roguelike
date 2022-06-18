// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RLCharacter.generated.h"

UCLASS()
class ROGUELIKE_API ARLCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARLCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// * Component 초기화
	virtual void PostInitializeComponents() override;

private:
	// * SpringArm
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraBoom;

	// * Camera
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FollowCamera;

	// * Combat Component
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class UCombatComponent* CombatComponent;

	// * MotionWarping Component
	UPROPERTY(VisibleAnywhere, Category = Combat)
	class UMotionWarpingComponent* MotionWarpingComponent;

	// * Inventory Component
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* InventoryComponent;

public:
	// * Combat Component Getter
	FORCEINLINE UCombatComponent* GetCombatComponent() const {return CombatComponent;}

	// * Inventory Component Getter
	FORCEINLINE UInventoryComponent* GetInventoryComponent() const {return InventoryComponent;}

	// * MotionWarping Component Getter
	FORCEINLINE UMotionWarpingComponent* GetMotionWarpingComponent() const {return MotionWarpingComponent;}

};
