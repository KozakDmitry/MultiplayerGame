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
	virtual void Fire();

  protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent *WeaponMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleSocket";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	float TraceMaxDistance = 1500;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float Damage;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MakeShot();
	void MakeDamage(FHitResult HitResult);

	APlayerController *GetPlayerController() const;
	bool GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;
	bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const;
	void MakeHit(FHitResult &HitResult, const FVector &TraceStart, const FVector &TraceEnd);
};
