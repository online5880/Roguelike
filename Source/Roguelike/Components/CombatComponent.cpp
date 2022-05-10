// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Roguelike/Character/RLCharacter.h"
#include "Roguelike/Character/RLCharacterAnimInstance.h"
#include "Roguelike/Character/RLPlayerController.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	WeaponType = ECharacterWeaponType::ECWT_Katana;
}

// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	if(AnimInstance)
	{
		AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this,&UCombatComponent::ComboNotifyBegin);
	}
}

// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCombatComponent::ComboNotifyBegin(FName NotifyName,
	const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	if(AnimInstance == nullptr && Character == nullptr) return;
	
	if(NotifyName.IsEqual(FName("Combo")))
	{
		ComboCount--;
		if(ComboCount < 0 && CurrentMontage)
		{
			AnimInstance->Montage_Stop(0.25f,(CurrentMontage));
			ComboCount = 0;
			CurrentMontage = nullptr;
		}
	}
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

void UCombatComponent::KatanaAttack()
{
	if(AnimInstance == nullptr && Character == nullptr) return;
	
	TArray<FString> MontageName;
	for(const TPair<FString, UAnimMontage*>& Map : KatanaMontageMap)
	{
		MontageName.Emplace(Map.Key);
	}
	const int32 Length(MontageName.Num()-1);
	const int32 Rand(FMath::RandRange(0,Length));
	
	if(KatanaMontageMap.Contains(MontageName[Rand]) && !KatanaMontageMap.IsEmpty())
	{
		if(AnimInstance->IsAnyMontagePlaying())
		{
			ComboCount = 1;
		}
		else
		{
			AnimInstance->Montage_Play(KatanaMontageMap.FindRef(MontageName[Rand]));
			CurrentMontage = KatanaMontageMap.FindRef(MontageName[Rand]);
		}
	}
}

void UCombatComponent::Dodge()
{
	if(Controller != nullptr)
	{
		if(Controller->IsInputKeyDown(EKeys::W))
		{
			DirectionType = ECharacterDirectionType::ECDT_Forward;
		}
		else if(Controller->IsInputKeyDown(EKeys::S))
		{
			DirectionType = ECharacterDirectionType::ECDT_Backward;
		}
		else if(Controller->IsInputKeyDown(EKeys::A))
		{
			DirectionType = ECharacterDirectionType::ECDT_Left;
		}
		else if(Controller->IsInputKeyDown(EKeys::D))
		{
			DirectionType = ECharacterDirectionType::ECDT_Right;
		}
		else return;
	}
	PlayDodgeMontage(DirectionType);
}


void UCombatComponent::PlayDodgeMontage(ECharacterDirectionType Type)
{
	if(AnimInstance == nullptr && Character == nullptr) return;

	if(!AnimInstance->IsAnyMontagePlaying())
	{
		const FRotator Look(UKismetMathLibrary::FindLookAtRotation(
	Character->GetActorLocation(),DodgeTargetLocation()));
		
		const FRotator Rot(Character->GetActorRotation());
		Character->SetActorRotation(FRotator(0.f,Look.Yaw,0.f));
		AnimInstance->Montage_Play(DodgeMap.FindRef(ECharacterDirectionType::ECDT_Forward));
	}
}

FVector UCombatComponent::DodgeTargetLocation()
{
	if(Character == nullptr) return FVector::ZeroVector;

	FVector RotX;
	if(Character->GetVelocity().Equals(FVector::ZeroVector,0.0001f))
	{
		RotX = Character->GetActorRotation().Vector();;		
	}
	else
	{
		RotX = Character->GetVelocity();
	}
	return Character->GetActorLocation()+(RotX.GetUnsafeNormal()*1.f);
}
