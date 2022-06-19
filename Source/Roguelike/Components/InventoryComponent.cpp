#include "InventoryComponent.h"

#include "Roguelike/Widget/InventoryWidget.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent() :
	InventoryWidgetClass(nullptr),
	InventoryWidget(nullptr),
	bOpenInventory(false)
{
	
}

void UInventoryComponent::Inventory()
{
	bOpenInventory = !bOpenInventory;
	if(bOpenInventory)
	{
		ShowInventory();
	}
	else
	{
		HideInventory();
	}
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UInventoryComponent::ShowInventory()
{
	if(InventoryWidgetClass)
	{
		InventoryWidget = Cast<UInventoryWidget>(CreateWidget(GetWorld(),InventoryWidgetClass));
		if(InventoryWidget)
		{
			InventoryWidget->AddToViewport();
			InventoryWidget->Update(Items);
		}
	}
}

void UInventoryComponent::HideInventory() const
{
	if(InventoryWidget)
	{
		InventoryWidget->RemoveFromParent();
	}
}

