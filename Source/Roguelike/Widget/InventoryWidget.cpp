#include "InventoryWidget.h"

#include "InventorySlotWidget.h"
#include "Components/UniformGridPanel.h"
#include "Roguelike/Item/Item.h"

void UInventoryWidget::Update(const TArray<TObjectPtr<AItem>> items)
{
	for(const TObjectPtr<AItem> item : items)
	{
		TObjectPtr<UInventorySlotWidget> ItemSlot =
			Cast<UInventorySlotWidget>(CreateWidget(GetWorld(),SlotClass));

		if(ItemSlot)
		{
			ItemSlot->Update(item.Get()->GetItemImage());
			SlotGridPanel.Get()->AddChild(ItemSlot);
		}
	}
}
