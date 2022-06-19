// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROGUELIKE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	// * 인벤토리 - Controller
	void Inventory();

	// * 인벤토리 아이템 배열
	UPROPERTY()
	TArray<TObjectPtr<class AItem>> Items;

protected:
	
	virtual void BeginPlay() override;

	// * 인벤토리 열기
	void ShowInventory();

	// * 인벤토리 닫기
	void HideInventory() const;

private:

	// * 인벤토리 클래스
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInventoryWidget> InventoryWidgetClass;

	// * 인벤토리 위젯
	UPROPERTY()
	TObjectPtr<UInventoryWidget> InventoryWidget;

	// * 인벤토리(Open/Close)
	bool bOpenInventory;

public:

};
