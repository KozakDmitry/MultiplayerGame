// Multiplayer Game

#include "Weapon/MGProjectile.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMGProjectile::AMGProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SetRootComponent(CollisionComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	MovementComponent->InitialSpeed = 2000.0f;
	MovementComponent->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void AMGProjectile::BeginPlay()
{
	Super::BeginPlay();
	check(MovementComponent);
	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	CollisionComponent->OnComponentHit.AddDynamic(this, &AMGProjectile::OnProjectileHit);
	SetLifeSpan(LifeSeconds);
}

void AMGProjectile::OnProjectileHit(UPrimitiveComponent *HitComponent, AActor *OtherActor,
									UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	if (!GetWorld())
	{
		MovementComponent->StopMovementImmediately();
		UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage,			//
											GetActorLocation(),			//
											DamageRadius,				//
											UDamageType::StaticClass(), //
											{GetOwner()},				//
											this,						//
											nullptr,					//
											DoFullDamage				//
		);

		DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, 5.0f);
		Destroy();
	}
}

AController *AMGProjectile::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}

// Called every frame
