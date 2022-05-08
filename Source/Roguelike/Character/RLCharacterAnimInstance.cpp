// Fill out your copyright notice in the Description page of Project Settings.


#include "RLCharacterAnimInstance.h"
#include "RLCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Roguelike/Components/CombatComponent.h"

void URLCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ARLCharacter>(TryGetPawnOwner());
}

void URLCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(Character == nullptr)
	{
		Character = Cast<ARLCharacter>(TryGetPawnOwner());
	}
	if(Character == nullptr) {return;}
	
	FVector Velocity = Character->GetVelocity();
	Velocity.Z = 0;
	Speed  = Velocity.Size();

	if(bIsAccelerating)
	{
		SpeedWhenStopping = Speed;
	}
	
	bIsInAir = Character->GetCharacterMovement()->IsFalling();
	bIsAccelerating = Character->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
	WeaponType = Character->GetCombatComponent()->GetWeaponType();

	Lean(DeltaSeconds);
}

void URLCharacterAnimInstance::Lean(float DeltaTime)
{
	if(Character == nullptr) return;
	
	CharacterRotationLastFrame = CharacterRotation;
	CharacterRotation = Character->GetActorRotation();
	
	const FRotator Delta(UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame));

	const float Target = (Delta.Yaw / DeltaTime);
	const float Interp(FMath::FInterpTo(YawDelta, Target, DeltaTime, 6.f));
	YawDelta = FMath::Clamp(Interp, -90.f, 90.f);
}
