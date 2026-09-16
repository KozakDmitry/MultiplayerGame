// Multiplayer Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MGBasePickUp.generated.h"

class USphereComponent;
UCLASS()
class MULTIPLAYERGAME_API AMGBasePickUp : public AActor
{
	GENERATED_BODY()

  public:
	// Sets default values for this actor's properties
	AMGBasePickUp();

  protected:
	// Called when the game starts or when spawned
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent *CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float RespawnTime = 5.0f;
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor *OtherActor) override;

  public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

  private:
	virtual bool GivePickUpTo(APawn *PlayerPawn);
	void PickupWasTaken();
	void Respawn();
};
