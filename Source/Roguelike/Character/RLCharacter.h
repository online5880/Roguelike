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
	virtual void PostInitializeComponents() override;

private:
	// * SpringArm
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraBoom;

	// * Camera
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FollowCamera;

	// * Combat Component
	UPROPERTY(VisibleAnywhere, Category = Combat)
	class UCombatComponent* CombatComponent;

public:
	// * Combat Component Getter
	FORCEINLINE UCombatComponent* GetCombatComponent() const {return CombatComponent;}

};
