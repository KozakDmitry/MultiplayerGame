// Multiplayer Game


#include "Weapon/MGBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"


DEFINE_LOG_CATEGORY_STATIC(BaseWeaponLog, All, All)


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
}
void AMGBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}
