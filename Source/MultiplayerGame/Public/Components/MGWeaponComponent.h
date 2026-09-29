// Multiplayer Game

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "MGCoreTypes.h"
#include "MGWeaponComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMGWeaponComponent, Display, All)

class AMGBaseWeapon;



UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MULTIPLAYERGAME_API UMGWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

  public:
	// Sets default values for this component's properties
	UMGWeaponComponent();

	virtual void StartFire();
	void StopFire();
	virtual void NextWeapon();
	void Reload();


	int32 GetCurrentWeapon() const;
	int32 CurrentWeaponIndex;

	bool GetWeaponUIData(FWeaponUIData &UIData) const;
	bool GetWeaponAmmoData(FAmmoData &AmmoData) const;


	bool TryToAddAmmo(TSubclassOf<AMGBaseWeapon> WeaponType, int32 ClipsAmount);



	FOnWeaponChange OnWeaponChange;
	FOnWeaponShoot OnWeaponShoot;
	FOnAmmoChange OnAmmoChanged;
  protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<FWeaponData> WeaponData;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UAnimMontage *EquipAnimMontage;
	UPROPERTY()
	AMGBaseWeapon *CurrentWeapon = nullptr;
	UPROPERTY()
	TArray<AMGBaseWeapon *> Weapons;
	virtual void BeginPlay() override;

	bool CanShoot() const;
	bool CanEquip() const;
	void EquipWeapon(int32 WeaponIndex);


  private:

	UPROPERTY()
	UAnimMontage *CurrentReloadAnimMontage = nullptr;

	bool EquipAnimInProgress = false;
	bool ReloadAnimInProgress = false;



	void SpawnWeapons();
	void AttachWeaponToSocket(AMGBaseWeapon *Weapon, USceneComponent *SceneComponent, const FName &SocketName);
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void PlayAnimMontage(UAnimMontage *Animation);
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
	void OnReloadFinished(USkeletalMeshComponent *MeshComponent);


	bool CanReload() const;

	void OnWeaponShot();
	void OnEmptyClip(AMGBaseWeapon* Weapon);
	void ChangeClip();


	
};
