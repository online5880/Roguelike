#pragma once

#define TRACE_LENGTH 80000.f

#define CUSTOM_DEPTH_PURPLE 250
#define CUSTOM_DEPTH_BLUE 251
#define CUSTOM_DEPTH_TAN 252

UENUM(BlueprintType)
enum class ECharacterWeaponType : uint8
{
	ECWT_Katana UMETA(DisplayName = "Katana"),
	
	
	EWT_DefaultMAX UMETA(DisplayName = "DefaultMAX")
};