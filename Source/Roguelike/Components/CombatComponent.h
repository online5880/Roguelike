// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Roguelike/Enum/CharacterWeaponType.h"
#include "CombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROGUELIKE_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	friend class ARLCharacter;
	UCombatComponent();

	// ! 공격
	void Attack();
	
	// ! 구르기
	void Dodge();

protected:
	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// ! Combo Notify Event
	UFUNCTION()
	void ComboNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);

	// ! Katana 공격
	void KatanaAttack();
	
private:

	// * 캐릭터 포인터
	UPROPERTY()
	ARLCharacter* Character;

	// * Character AnimInstance
	UPROPERTY()
	class URLCharacterAnimInstance* AnimInstance;

	// * 컨트롤러 포인터
	UPROPERTY()
	class ARLPlayerController* Controller;

	// * 무기 타입
	ECharacterWeaponType WeaponType;

	// * Katana Montage Map
	UPROPERTY(EditAnywhere,Category = "Montage|Katana")
	TMap<FString, UAnimMontage*> KatanaMontageMap;

	// * 콤보 체크
	int32 ComboCount;

	// * 현재 Montage Ref
	UPROPERTY()
	UAnimMontage* CurrentMontage;


public:
	// * 무기 타입 Getter
	FORCEINLINE ECharacterWeaponType GetWeaponType() const {return WeaponType;}
};