// Multiplayer Game


#include "Weapon/MGLauncherWeapon.h"
#include "Weapon/MGProjectile.h"

void AMGLauncherWeapon::StartFire()
{
	MakeShot();
}

void AMGLauncherWeapon::MakeShot()
{
	if (!GetWorld()||IsAmmoEmpty())
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

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();


	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	AMGProjectile* Projectile = GetWorld()->SpawnActorDeferred<AMGProjectile>(ProjectileClass, SpawnTransform);
	if (Projectile)
	{
		Projectile->SetShotDirection(Direction);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
	}
	//Set params to Do
	DecreaseAmmo();
}

