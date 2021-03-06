// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Roguelike/Enum/CharacterMovementType.h"
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

	// * Dodge Montage 실행
	void PlayDodgeMontage(const FName& DodgeName);

	// * Dodge MotionWarping Update - Location, Rotation
	void DodgeMotionWarping() const;

	// * Dodge End Event
	void DodgeEnded(UAnimMontage*, bool);

private:

	// * 캐릭터 포인터
	UPROPERTY()
	TObjectPtr<ARLCharacter> Character;

	// * Character AnimInstance
	UPROPERTY()
	TObjectPtr<class URLCharacterAnimInstance> AnimInstance;

	// * 컨트롤러 포인터
	UPROPERTY()
	TObjectPtr<class ARLPlayerController> Controller;

	// * 무브먼트 타입
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ECharacterMovementType MovementType;

	// * 무기 타입
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ECharacterWeaponType WeaponType;

	// * Katana Montage Map
	UPROPERTY(EditAnywhere,Category = "Montage|Katana")
	TMap<FString, TObjectPtr<UAnimMontage>> KatanaMontageMap;

	// * 콤보 체크
	int32 ComboCount;

	// * 현재 Montage Ref
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> CurrentMontage;

	// * 구르는 중인가?
	bool bIsDodge;

	// * Dodge Montage Map
	UPROPERTY(EditAnywhere,Category = "Montage|Dodge")
	TMap<FName, TObjectPtr<UAnimMontage>> DodgeMap;

	// * Dodge 거리
	UPROPERTY(EditAnywhere,Category = "Dodge")
	float DodgeDistance;

public:
	// * 무기 타입 Getter
	FORCEINLINE ECharacterWeaponType GetWeaponType() const {return WeaponType;}
};