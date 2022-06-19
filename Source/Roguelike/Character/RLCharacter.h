// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Roguelike/Interface/InventoryInterface.h"
#include "RLCharacter.generated.h"

UCLASS()
class ROGUELIKE_API ARLCharacter : public ACharacter, public IInventoryInterface
{
	GENERATED_BODY()

public:
	ARLCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// * Component 초기화
	virtual void PostInitializeComponents() override;

	// * 인벤토리 상호작용 - Inventory Interface
	virtual void InventoryInteract(const TObjectPtr<AItem> item) override;

private:
	// * SpringArm
	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<class USpringArmComponent> CameraBoom;

	// * Camera
	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<class UCameraComponent> FollowCamera;

	// * Combat Component
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCombatComponent> CombatComponent;

	// * MotionWarping Component
	UPROPERTY(VisibleAnywhere, Category = Combat)
	TObjectPtr<class UMotionWarpingComponent> MotionWarpingComponent;

	// * Inventory Component
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInventoryComponent> InventoryComponent;

public:
	// * Follow Camera Getter
	FORCEINLINE TObjectPtr<UCameraComponent> GetFollowCamera() const {return FollowCamera;}
	
	// * Combat Component Getter
	FORCEINLINE TObjectPtr<UCombatComponent> GetCombatComponent() const {return CombatComponent;}

	// * Inventory Component Getter
	FORCEINLINE TObjectPtr<UInventoryComponent> GetInventoryComponent() const {return InventoryComponent;}

	// * MotionWarping Component Getter
	FORCEINLINE TObjectPtr<UMotionWarpingComponent> GetMotionWarpingComponent() const {return MotionWarpingComponent;}

};
