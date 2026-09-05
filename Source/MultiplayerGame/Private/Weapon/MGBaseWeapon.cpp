// Multiplayer Game

#include "Weapon/MGBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "MGBaseCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(BaseWeaponLog, All, All)
UE_DISABLE_OPTIMIZATION
// Sets default values
AMGBaseWeapon::AMGBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}
void AMGBaseWeapon::Fire()
{
	UE_LOG(BaseWeaponLog, Display, TEXT("IS FIRING!"));
	MakeShot();
}
void AMGBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMesh);
}

void AMGBaseWeapon::MakeShot()
{
	if (!GetWorld())
	{
		return;
	}

		FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
	{
		return;
	}
	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	if (HitResult.bBlockingHit)
	{
		
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
		//UE_LOG(BaseWeaponLog, Display, TEXT("Bone: %s"), *HitResult.BoneName.ToString());

		
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	}
}

void AMGBaseWeapon::MakeDamage(FHitResult HitResult)
{
	AActor *HitActor = HitResult.GetActor();
	if (!HitActor)
	{
		return;
	}
	AMGBaseCharacter *HitCharacter = Cast<AMGBaseCharacter>(HitActor);
	if (!HitCharacter)
	{
		return;
	}
	HitCharacter->TakeDamage(Damage, FDamageEvent{}, GetPlayerController(), this);
}

APlayerController *AMGBaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player)
	{
		return nullptr;
	}
	return Player->GetController<APlayerController>();
}

bool AMGBaseWeapon::GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const
{
	const auto Controller = GetPlayerController();
	if (!Controller)
	{
		return false;
	}

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	return true;
}
FVector AMGBaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool AMGBaseWeapon::GetTraceData(FVector &TraceStart, FVector &TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
	{
		return false;
	}
	TraceStart = ViewLocation;
	const FVector ShootDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void AMGBaseWeapon::MakeHit(FHitResult &HitResult, const FVector &TraceStart, const FVector &TraceEnd)
{
	if (!GetWorld())
		return;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility,
										 CollisionParams);
}

UE_ENABLE_OPTIMIZATION
