// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKE_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// * 인벤토리 업데이트
	void Update(const TArray<TObjectPtr<class AItem>> items);

private:
	// * 슬롯 Class
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInventorySlotWidget> SlotClass;

	// * 슬롯 그리드 패널
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUniformGridPanel> SlotGridPanel;
};
