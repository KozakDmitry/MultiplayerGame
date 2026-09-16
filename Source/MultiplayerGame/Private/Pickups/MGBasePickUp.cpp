// Multiplayer Game


#include "Pickups/MGBasePickUp.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickUp, All, All);

// Sets default values
AMGBasePickUp::AMGBasePickUp()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

}

// Called when the game starts or when spawned
void AMGBasePickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMGBasePickUp::NotifyActorBeginOverlap(AActor *OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	UE_LOG(LogBasePickUp, Display, TEXT("Pickup was taken"));
	Destroy();
}

// Called every frame
void AMGBasePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

