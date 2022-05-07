#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/SkeletalMesh.h"

#include "CharacterModuleDataTable.generated.h"

USTRUCT(BlueprintType)
struct FCharacterModuleDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	FString Description;

	UPROPERTY(EditAnywhere)
	TArray<USkeletalMesh*> Mesh;

	UPROPERTY(EditAnywhere)
	TArray<UTexture2D*> Thumbnail;
};
