// Multiplayer Game

#include "Components/MGWeaponComponent.h"
#include "Animations/MGReloadAnimNotify.h"
#include "Animations/UMGEquipAnimNotify.h"
#include "Animations/AnimUtils.h"
#include "GameFramework/Character.h"
#include "Weapon/MGBaseWeapon.h"



DEFINE_LOG_CATEGORY(LogMGWeaponComponent)

constexpr static int32 WeaponNum = 2;

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

	checkf(WeaponData.Num() == WeaponNum, TEXT("CAN HOLD ONLY %i WEAPONS"), WeaponNum);
	
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

	for (auto OneWeaponData : WeaponData)
	{
		auto Weapon = GetWorld()->SpawnActor<AMGBaseWeapon>(OneWeaponData.WeaponClass);
		if (!Weapon)
		{
			continue;
		}
		Weapon->OnClipEmpty.AddUObject(this, &UMGWeaponComponent::OnEmptyClip);
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
	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
	{
		UE_LOG(LogMGWeaponComponent, Warning, TEXT("Invalid Weapon index"));
		return;
	}
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
	// CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
	const auto CurrentWeaponData = WeaponData.FindByPredicate(
		[&](const FWeaponData &Data) { return Data.WeaponClass == CurrentWeapon->GetClass(); });
	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
	EquipAnimInProgress = true;
	PlayAnimMontage(EquipAnimMontage);
}
void UMGWeaponComponent::NextWeapon()
{
	if (!CanEquip())
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

	auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<UMGEquipAnimNotify>(EquipAnimMontage);
	if (EquipFinishedNotify)
	{
		EquipFinishedNotify->OnNotified.AddUObject(this, &UMGWeaponComponent::OnEquipFinished);
	}
	else
	{
		UE_LOG(LogMGWeaponComponent, Error, TEXT("Equip anim notify is forgotten to set"));
		checkNoEntry();
	}
	for (auto OneWeaponData : WeaponData)
	{
		auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<UMGReloadAnimNotify>(OneWeaponData.ReloadAnimMontage);
		if (!ReloadFinishedNotify)
		{
			UE_LOG(LogMGWeaponComponent, Error, TEXT("Reload anim notify is forgotten to set"));
			checkNoEntry();
		}

		ReloadFinishedNotify->OnNotified.AddUObject(this, &UMGWeaponComponent::OnReloadFinished);
	}
}
void UMGWeaponComponent::OnReloadFinished(USkeletalMeshComponent *MeshComponent)
{
	ACharacter *Character = Cast<ACharacter>(GetOwner());
	if (!Character || Character->GetMesh() != MeshComponent)
	{
		return;
	}
	ReloadAnimInProgress = false;
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

void UMGWeaponComponent::Reload()
{
	ChangeClip();
}

bool UMGWeaponComponent::CanShoot() const
{
	return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool UMGWeaponComponent::CanEquip() const
{
	return !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool UMGWeaponComponent::CanReload() const
{
	return CurrentWeapon			//
		   && !EquipAnimInProgress	//
		   && !ReloadAnimInProgress //
		   && CurrentWeapon->CanReload();
}

void UMGWeaponComponent::OnEmptyClip()
{
	ChangeClip();
}

void UMGWeaponComponent::ChangeClip()
{
	if (!CanReload())
	{
		return;
	}
	CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();
	ReloadAnimInProgress = true;
	PlayAnimMontage(CurrentReloadAnimMontage);
}
