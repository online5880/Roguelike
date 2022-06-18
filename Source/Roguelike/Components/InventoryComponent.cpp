#include "InventoryComponent.h"

#include "Roguelike/Widget/InventoryWidget.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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

