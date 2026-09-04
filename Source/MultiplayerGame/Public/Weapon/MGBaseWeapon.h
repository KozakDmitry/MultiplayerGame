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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
