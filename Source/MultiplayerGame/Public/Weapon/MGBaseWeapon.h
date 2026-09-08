// Multiplayer Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MGCoreTypes.h"
#include "MGBaseWeapon.generated.h"


class USkeletalMeshComponent;



UCLASS()
class MULTIPLAYERGAME_API AMGBaseWeapon : public AActor
{
	GENERATED_BODY()

  public:
	// Sets default values for this actor's properties
	AMGBaseWeapon();

	FOnClipEmptySignature OnClipEmpty;
	virtual void StartFire();
	virtual void StopFire();

	void ChangeClip();
	bool CanReload() const;

  protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent *WeaponMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleSocket";
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	float TraceMaxDistance = 1500;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	FAmmoData DefaultAmmo{15, 10, false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float Damage = 2.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void MakeShot();
	virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const;

	void MakeDamage(FHitResult HitResult);

	APlayerController *GetPlayerController() const;
	bool GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;
	void MakeHit(FHitResult &HitResult, const FVector &TraceStart, const FVector &TraceEnd);
	
	void DecreaseAmmo();
	bool IsAmmoEmpty() const;
	bool IsClipEmpty() const;
	void LogAmmo();

  private:
	FAmmoData CurrentAmmo;

};
