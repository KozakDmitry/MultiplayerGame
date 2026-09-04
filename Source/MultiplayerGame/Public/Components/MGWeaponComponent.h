// Multiplayer Game

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "MGWeaponComponent.generated.h"


class AMGBaseWeapon;


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MULTIPLAYERGAME_API UMGWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

  public:
	// Sets default values for this component's properties
	UMGWeaponComponent();

	void Fire();

  protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AMGBaseWeapon> WeaponClass;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponAttackPointName = "WeaponSocket";
	virtual void BeginPlay() override;

  private:
	UPROPERTY()
	AMGBaseWeapon *CurrentWeapon = nullptr;
	void SpawnWeapon();
};
