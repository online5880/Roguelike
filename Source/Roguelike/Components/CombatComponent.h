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

	void Attack();

protected:
	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void KatanaAttack();

private:

	// * 캐릭터 포인터
	UPROPERTY()
	ARLCharacter* Character;

	// * 컨트롤러 포인터
	UPROPERTY()
	class ARLPlayerController* Controller;

	// * 무기 타입
	ECharacterWeaponType WeaponType;

	UPROPERTY(EditAnywhere,Category = "Montage|Katana")
	TMap<FString, UAnimMontage*> KatanaMontageMap;

	bool bIsCombo;

public:
	// * 무기 타입 Getter
	FORCEINLINE ECharacterWeaponType GetWeaponType() const {return WeaponType;}
};