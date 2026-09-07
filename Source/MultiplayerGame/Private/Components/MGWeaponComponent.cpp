// Multiplayer Game

#include "Components/MGWeaponComponent.h"
#include "Animations/MGAnimNotify.h"
#include "GameFramework/Character.h"
#include "Weapon/MGBaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogMGWeaponComponent, All, All)

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
	if (!CanShoot())
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
	InitAnimations();
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
}

void UMGWeaponComponent::SpawnWeapons()
{

	ACharacter *Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld())
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

void UMGWeaponComponent::AttachWeaponToSocket(AMGBaseWeapon *Weapon, USceneComponent *SceneComponent,
											  const FName &SocketName)
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
	EquipAnimInProgress = true;
	PlayAnimMontage(EquipAnimMontage);
}
void UMGWeaponComponent::NextWeapon()
{
	if (EquipAnimInProgress)
	{
		return;
	}
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}

void UMGWeaponComponent::PlayAnimMontage(UAnimMontage *Animation)
{
	ACharacter *Character = Cast<ACharacter>(GetOwner());
	if (!Character)
	{
		return;
	}
	Character->PlayAnimMontage(Animation);
}

void UMGWeaponComponent::InitAnimations()
{
	if (!EquipAnimMontage)
	{
		return;
	}
	const auto NotifyEvents = EquipAnimMontage->Notifies;
	for (auto NotifyEvent : NotifyEvents)
	{
		auto EquipFinishNotify = Cast<UMGAnimNotify>(NotifyEvent.Notify);
		if (EquipFinishNotify)
		{
			EquipFinishNotify->OnNotified.AddUObject(this, &UMGWeaponComponent::OnEquipFinished);
			break;
		}
	}
}

void UMGWeaponComponent::OnEquipFinished(USkeletalMeshComponent *MeshComponent)
{
	ACharacter *Character = Cast<ACharacter>(GetOwner());
	if (!Character || Character->GetMesh() != MeshComponent)
	{
		return;
	}
	EquipAnimInProgress = false;
}

bool UMGWeaponComponent::CanShoot() const
{
	return CurrentWeapon&&!EquipAnimInProgress;
}

bool UMGWeaponComponent::CanEquip() const
{
	return !EquipAnimInProgress;
}
