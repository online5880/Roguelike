// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"

#include "Components/Image.h"

void UInventorySlotWidget::Update(const TObjectPtr<UTexture2D> Image)
{
	ItemImage.Get()->SetBrushFromTexture(Image);
}
