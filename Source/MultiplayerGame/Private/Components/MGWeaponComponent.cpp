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

void UMGWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();
	Super::EndPlay(EndPlayReason);
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

	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
}

void UMGWeaponComponent::SpawnWeapons()
{
	
	ACharacter *Character = Cast<ACharacter>(GetOwner());
	if (!Character|| !GetWorld())
	{
		return;
	}

	for (auto WeaponClass : WeaponClasses)
	{
		auto Weapon = GetWorld()->SpawnActor<AMGBaseWeapon>(WeaponClass);
		if (!Weapon)
		{
			continue;
		}
		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}
	
	
}

void UMGWeaponComponent::AttachWeaponToSocket(AMGBaseWeapon *Weapon, USceneComponent *SceneComponent, const FName& SocketName)
{
	if (!Weapon || !SceneComponent)
	{
		return;
	}
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}
void UMGWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	ACharacter *Character = Cast<ACharacter>(GetOwner());
	if (!Character)
	{
		return;
	}
	if (CurrentWeapon)
	{
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
		StopFire();
	}
	CurrentWeapon = Weapons[WeaponIndex];
	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
}
void UMGWeaponComponent::NextWeapon()
{
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}
