// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RLCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKE_API URLCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// *  캐릭터 기울기
	void Lean(float DeltaTime);

private:

	// * Character
	UPROPERTY(BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	class ARLCharacter* Character;

	// * 속도
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float Speed;

	// * 멈추기 전 속도
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float SpeedWhenStopping;

	// * 공중에 있는지 체크
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsInAir;
	
	// * 움직이는 중인지 체크
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsAccelerating;

	// * Yaw Value
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float YawDelta;

	// ? 캐릭터 회전값 (현재,마지막)
	FRotator CharacterRotation;
	FRotator CharacterRotationLastFrame;
};
