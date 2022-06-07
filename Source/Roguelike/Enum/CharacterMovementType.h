#pragma once

UENUM(BlueprintType)
enum class ECharacterMovementType : uint8
{
	ECMT_Idle UMETA(DisplayName = "Idle"),
	ECMT_Walk UMETA(DisplayName = "Walk"),
	ECMT_Run UMETA(DisplayName = "Run"),
	ECMT_Dodge UMETA(DisplayName = "Dodge"),
	
	ECMT_DefaultMAX UMETA(DisplayName = "DefaultMAX")
};

/*UENUM(BlueprintType)
enum class ECharacterDirectionType : uint8
{
	ECDT_Forward UMETA(DisplayName = "Forward"),
	ECDT_Backward UMETA(DisplayName = "Backward"),
	ECDT_Left UMETA(DisplayName = "Left"),
	ECDT_Right UMETA(DisplayName = "Right"),
	
	ECDT_DefaultMAX UMETA(DisplayName = "DefaultMAX")
};*/