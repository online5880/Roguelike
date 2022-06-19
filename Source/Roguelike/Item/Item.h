// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Roguelike/Interface/InventoryInterface.h"
#include "Item.generated.h"

UCLASS()
class ROGUELIKE_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


private:
	// * Root Component
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> Root;

	// * Item Mesh
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	// *  상호작용 콜리전
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USphereComponent> InteractCollision;

	// * 아이템 속성(임시)
	UPROPERTY(EditAnywhere)
	FText Name;
	UPROPERTY(EditAnywhere)
	FText Description;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2D> Image;

public:
	
	FORCEINLINE FText GetItemName() const {return Name;}
	FORCEINLINE FText GetItemDescription() const {return Description;}
	FORCEINLINE TObjectPtr<UTexture2D> GetItemImage() const {return Image;}
	

};
