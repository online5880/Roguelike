// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "Components/SphereComponent.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(GetRootComponent());
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	InteractCollision = CreateDefaultSubobject<USphereComponent>(TEXT("InteractCollision"));
	InteractCollision->SetupAttachment(ItemMesh);
	InteractCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
	InteractCollision->OnComponentBeginOverlap.AddDynamic(this,&AItem::OnOverlapBegin);
	InteractCollision->OnComponentEndOverlap.AddDynamic(this,&AItem::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const TObjectPtr<IInventoryInterface> InventoryInterface = Cast<IInventoryInterface>(OtherActor);
	if(InventoryInterface)
	{
		Destroy();
		InventoryInterface->InventoryInteract(this);
	}
}

void AItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	
}

