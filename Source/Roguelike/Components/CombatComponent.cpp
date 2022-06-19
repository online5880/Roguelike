#include "CombatComponent.h"
#include "MotionWarpingComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Roguelike/Character/RLCharacter.h"
#include "Roguelike/Character/RLCharacterAnimInstance.h"

UCombatComponent::UCombatComponent() :
	Character(nullptr),
	AnimInstance(nullptr),
	Controller(nullptr),
	MovementType(ECharacterMovementType::ECMT_Idle),
	WeaponType(ECharacterWeaponType::ECWT_Katana),
	ComboCount(0),
	CurrentMontage(nullptr),
	bIsDodge(false),
	DodgeDistance(500.f)
{
	PrimaryComponentTick.bCanEverTick = true;
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
			AnimInstance->Montage_Stop(0.33f,(CurrentMontage));
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
	for(const TPair<FString, TObjectPtr<UAnimMontage>>& Map : KatanaMontageMap)
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
	PlayDodgeMontage("Normal");
}


void UCombatComponent::PlayDodgeMontage(const FName& DodgeName)
{
	if(AnimInstance == nullptr && Character == nullptr) return;

	const bool bCanDodge = (
		!AnimInstance->IsAnyMontagePlaying() &&
		MovementType != ECharacterMovementType::ECMT_Dodge);

	if(bCanDodge)
	{
		FOnMontageEnded MontageEnded;
		MontageEnded.BindUObject(this,&UCombatComponent::DodgeEnded);
		
		MovementType = ECharacterMovementType::ECMT_Dodge;
		DodgeMotionWarping();
		AnimInstance->Montage_Play(DodgeMap.FindRef(DodgeName));
		CurrentMontage = DodgeMap.FindRef(DodgeName);
		AnimInstance->Montage_SetEndDelegate(MontageEnded,CurrentMontage);
	}
}

void UCombatComponent::DodgeMotionWarping() const
{
	if(Character == nullptr && Character->GetMotionWarpingComponent() == nullptr) return;

	const FVector MovementInputVector = Character->GetLastMovementInputVector();
	const FVector PlayerLoc = Character->GetActorLocation();
	const FVector TargetLoc = (PlayerLoc + (DodgeDistance * MovementInputVector.GetSafeNormal()));
	const FRotator TargetRot = UKismetMathLibrary::MakeRotFromX(MovementInputVector);

	// * 안움직일 경우 - 앞으로 구르기
	if(MovementInputVector.IsZero())
	{
		const FVector ForwardLoc = (PlayerLoc + (DodgeDistance * Character->GetActorForwardVector().GetSafeNormal()));
		const FRotator ForwardRot = UKismetMathLibrary::MakeRotFromX(Character->GetActorForwardVector());
		Character->GetMotionWarpingComponent()->AddOrUpdateWarpTargetFromLocationAndRotation(
		"Dodge",
		ForwardLoc,
		ForwardRot);
		return;
	}

	Character->GetMotionWarpingComponent()->AddOrUpdateWarpTargetFromLocationAndRotation(
		"Dodge",
		TargetLoc,
		TargetRot);
}

void UCombatComponent::DodgeEnded(UAnimMontage*, bool)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, __FUNCTION__);
	MovementType = ECharacterMovementType::ECMT_Idle;
	CurrentMontage = nullptr;
}
