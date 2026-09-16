#pragma once

#include "MGCoreTypes.generated.h"

class AMGBaseWeapon;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, AMGBaseWeapon*)
DECLARE_MULTICAST_DELEGATE(FOnShot)

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(ForHealthChange, float)
DECLARE_MULTICAST_DELEGATE_OneParam(ForWeaponChange, int32)
DECLARE_MULTICAST_DELEGATE_OneParam(ForWeaponShoot, int32)
DECLARE_MULTICAST_DELEGATE(ForAmmoChange)

class UAnimMontage;
class UTexture2D;

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Bullets;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
	int32 Clips;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool Infinite;
};

//Weapon
USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AMGBaseWeapon> WeaponClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UAnimMontage *ReloadAnimMontage;
};


USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	UTexture2D *MainIcon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	UTexture2D *CrossHairIcon;
};