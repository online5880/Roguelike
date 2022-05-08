// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"

#include "Roguelike/Character/RLCharacter.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	WeaponType = ECharacterWeaponType::ECWT_Katana;
}

void UCombatComponent::Attack()
{
	switch (WeaponType)
	{
	case ECharacterWeaponType::ECWT_Katana:
		KatanaAttack();
		break;
	case ECharacterWeaponType::EWT_DefaultMAX:
		break;
	}
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCombatComponent::KatanaAttack()
{
	const FString Str(FString("Attack 1"));
	if(KatanaMontageMap.Contains(Str))
	{
		Character->GetMesh()->GetAnimInstance()->Montage_Play(
			KatanaMontageMap[Str]);
	}
}