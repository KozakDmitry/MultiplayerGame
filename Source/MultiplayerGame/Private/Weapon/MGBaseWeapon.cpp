// Multiplayer Game

#include "Weapon/MGBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "Engine/World.h"
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
void AMGBaseWeapon::StartFire()
{
}
void AMGBaseWeapon::StopFire()
{
}
void AMGBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMesh);
	checkf(DefaultAmmo.Bullets > 0, TEXT("Bullets count couldn't be<=0"));
	checkf(DefaultAmmo.Clips > 0, TEXT("Clips count couldn't be<=0"));
	CurrentAmmo = DefaultAmmo;
}

void AMGBaseWeapon::MakeShot()
{
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

void AMGBaseWeapon::DecreaseAmmo()
{
	if (CurrentAmmo.Bullets == 0)
	{
		UE_LOG(BaseWeaponLog, Warning, TEXT("Clip is empty"));
		return;
	}
	CurrentAmmo.Bullets--;
	LogAmmo();
	OnShot.Broadcast();
	if (IsClipEmpty() && !IsAmmoEmpty())
	{
		StopFire();
		OnClipEmpty.Broadcast(this);
	}
}

bool AMGBaseWeapon::IsAmmoEmpty() const
{
	return CurrentAmmo.Clips == 0 && IsClipEmpty() && !CurrentAmmo.Infinite;
}

bool AMGBaseWeapon::IsClipEmpty() const
{
	return CurrentAmmo.Bullets == 0;
}

bool AMGBaseWeapon::IsAmmoFull() const
{
	return CurrentAmmo.Clips == DefaultAmmo.Clips && CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

void AMGBaseWeapon::ChangeClip()
{
	if (!CurrentAmmo.Infinite)
	{
		if (CurrentAmmo.Clips == 0)
		{
			UE_LOG(BaseWeaponLog, Warning, TEXT("No more clips"));
			return;
		}
		CurrentAmmo.Clips--;
	}
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	
}

bool AMGBaseWeapon::CanReload() const
{
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}

bool AMGBaseWeapon::TryToAddAmmo(int32 ClipsAmount)
{
	if (CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount <= 0)
	{
		return false;
	}
	if (IsAmmoEmpty())
	{
		CurrentAmmo.Clips = FMath::Clamp(ClipsAmount, 0, DefaultAmmo.Clips + 1);
		OnClipEmpty.Broadcast(this);
	}
	else if (CurrentAmmo.Clips < DefaultAmmo.Clips)
	{
		const auto NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
		if (DefaultAmmo.Clips - NextClipsAmount >= 0)
		{
			CurrentAmmo.Clips = NextClipsAmount;
			UE_LOG(BaseWeaponLog, Display, TEXT("Clips were added"));
		}
		else
		{
			CurrentAmmo.Clips = DefaultAmmo.Clips;
			CurrentAmmo.Bullets = DefaultAmmo.Bullets;
			UE_LOG(BaseWeaponLog, Display, TEXT("Ammo is full now"));

		}
	}
	else
	{
		CurrentAmmo.Bullets = DefaultAmmo.Bullets;
		UE_LOG(BaseWeaponLog, Display, TEXT("Bullets were added"));

	}
	return true;
}

void AMGBaseWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
	AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
	UE_LOG(BaseWeaponLog, Display, TEXT("%s"), *AmmoInfo);
}

UE_ENABLE_OPTIMIZATION
