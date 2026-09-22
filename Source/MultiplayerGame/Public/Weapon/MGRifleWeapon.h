// Multiplayer Game

#pragma once

#include "CoreMinimal.h"
#include "Weapon/MGBaseWeapon.h"
#include "MGRifleWeapon.generated.h"

class UMGWeaponFXComponent;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class MULTIPLAYERGAME_API AMGRifleWeapon : public AMGBaseWeapon
{
	GENERATED_BODY()

  public:
	AMGRifleWeapon();

	virtual void StartFire() override;
	virtual void StopFire() override;

  protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TimeBetweenShots = 0.1f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float BulletSpread = 1.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UMGWeaponFXComponent *WeaponFXComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem *TraceFX;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FString TraceTargetName = "TraceTarget";
	virtual void BeginPlay() override;
	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const override;


  private:
	FTimerHandle ShotTimerHandle;
	UPROPERTY()
	UNiagaraComponent *MuzzleFXComponent;

	void InitMuzzleFX();
	void SetMuzzleFXVisibility(bool Visible);
	void SpawnTraceFX(const FVector &TraceStart, const FVector &TraceEnd);
};
