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

	void StartFire();
	void StopFire();
	void NextWeapon();


  protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<TSubclassOf<AMGBaseWeapon>> WeaponClasses;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UAnimMontage *EquipAnimMontage;

	virtual void BeginPlay() override;

  private:
	UPROPERTY()
	AMGBaseWeapon *CurrentWeapon = nullptr;
	UPROPERTY()
	TArray<AMGBaseWeapon *> Weapons;
	int32 CurrentWeaponIndex;
	bool EquipAnimInProgress = false;




	void SpawnWeapons();
	void AttachWeaponToSocket(AMGBaseWeapon *Weapon, USceneComponent *SceneComponent, const FName &SocketName);
	void EquipWeapon(int32 WeaponIndex);
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void PlayAnimMontage(UAnimMontage *Animation);
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

	bool CanShoot() const;
	bool CanEquip() const;
};
