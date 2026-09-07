// Multiplayer Game

#include "Components/MGWeaponComponent.h"
#include "GameFramework/Character.h"
#include "Weapon/MGBaseWeapon.h"

// Sets default values for this component's properties
UMGWeaponComponent::UMGWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these
	// features off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UMGWeaponComponent::StartFire()
{
	if (!CurrentWeapon)
	{
		return;
	}

	CurrentWeapon->StartFire();
}
void UMGWeaponComponent::StopFire()
{
	if (!CurrentWeapon)
	{
		return;
	}

	CurrentWeapon->StopFire();
}
// Called when the game starts
void UMGWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
	// ...
}

void UMGWeaponComponent::SpawnWeapon()
{
	if (!GetWorld())
	{
		return;
	}
	ACharacter *Character = Cast<ACharacter>(GetOwner());
	if (!Character)
	{
		return;
	}
	CurrentWeapon = GetWorld()->SpawnActor<AMGBaseWeapon>(WeaponClass);
	if (!CurrentWeapon)
	{
		return;
	}
	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttackPointName);
	CurrentWeapon->SetOwner(GetOwner());
}
// Called every frame
