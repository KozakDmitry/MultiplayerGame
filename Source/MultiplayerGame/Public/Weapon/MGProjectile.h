// Multiplayer Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MGProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class MULTIPLAYERGAME_API AMGProjectile : public AActor
{
	GENERATED_BODY()

  public:
	// Sets default values for this actor's properties
	AMGProjectile();
	void SetShotDirection(const FVector &Direction)
	{
		ShotDirection = Direction;
	}

  protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	USphereComponent *CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	UProjectileMovementComponent *MovementComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	float DamageRadius = 200.0f;
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	float Damage = 50.0f;
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	bool DoFullDamage = false;
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	float LifeSeconds = 5.0f;
	// Called when the game starts or when spawned

	virtual void BeginPlay() override;

  private:
	FVector ShotDirection;

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);
	AController *GetController() const;

};
