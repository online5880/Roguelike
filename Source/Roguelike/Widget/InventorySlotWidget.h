// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKE_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

	
public:
	// * 슬롯 업데이트
	void Update(const TObjectPtr<UTexture2D> Image);

private:
	// * 아이템 이미지(임시)
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> ItemImage;

};
