// Multiplayer Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MGBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class MULTIPLAYERGAME_API AMGBaseWeapon : public AActor
{
	GENERATED_BODY()

  public:
	// Sets default values for this actor's properties
	AMGBaseWeapon();
	virtual void StartFire();
	virtual void StopFire();

  protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent *WeaponMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleSocket";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	float TraceMaxDistance = 1500;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float Damage=2.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void MakeShot();
	virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const;

	void MakeDamage(FHitResult HitResult);

	APlayerController *GetPlayerController() const;
	bool GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;
	void MakeHit(FHitResult &HitResult, const FVector &TraceStart, const FVector &TraceEnd);


};
