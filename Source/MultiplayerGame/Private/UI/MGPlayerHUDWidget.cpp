// Multiplayer Game

#include "UI/MGPlayerHUDWidget.h"
#include "Components/Image.h"
#include "Components/MGHealthComponent.h"
#include "Components/MGWeaponComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GameFramework/Pawn.h"

void UMGPlayerHUDWidget::UpdateHealth(float HealthPercent)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(HealthPercent);
	}
}
void UMGPlayerHUDWidget::UpdateWeapon(int32 Index)
{
	FWeaponUIData WeaponData;
	if (WeaponComponentRef->GetWeaponUIData(WeaponData))
	{
		if (CrossHairImage && WeaponData.CrossHairIcon)
		{
			CrossHairImage->SetBrushFromTexture(WeaponData.CrossHairIcon);
		}
		if (WeaponImage && WeaponData.MainIcon)
		{
			WeaponImage->SetBrushFromTexture(WeaponData.MainIcon);
		}
	}
}

bool UMGPlayerHUDWidget::GetWeaponUIData(FWeaponUIData &UIData) const
{
	const auto WeaponComponent = GetComponent<UMGWeaponComponent>();

	if (WeaponComponent)
	{
		return WeaponComponent->GetWeaponUIData(UIData);
	}
	return false;
}

bool UMGPlayerHUDWidget::GetWeaponAmmoData(FAmmoData &AmmoData) const
{
	if (WeaponComponentRef)
	{
		return WeaponComponentRef->GetWeaponAmmoData(AmmoData);
	}
	return false;
}

bool UMGPlayerHUDWidget::IsPlayerAlive() const
{
	if (HealthComponentRef)
	{
		return !HealthComponentRef->IsDead();
	}
	return false;
}

bool UMGPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

void UMGPlayerHUDWidget::UpdateAmmo()
{
	FAmmoData AmmoData;
	if (GetWeaponAmmoData(AmmoData))
	{
		const auto ClipsText = AmmoData.Infinite ? TEXT("∞") : FText::AsNumber(AmmoData.Clips).ToString();
		const auto AmmoString =
			FString::Printf(TEXT("%s / %s"), *FText::AsNumber(AmmoData.Bullets).ToString(), *ClipsText);
		if (AmmoTextBlock)
		{
			AmmoTextBlock->SetText(FText::FromString(AmmoString));
		}
	}
}

template <typename T> T *UMGPlayerHUDWidget::GetComponent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player)
		return nullptr;

	const auto Component = Player->GetComponentByClass(T::StaticClass());
	return Cast<T>(Component);
}
void UMGPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	WeaponComponentRef = GetComponent<UMGWeaponComponent>();
	HealthComponentRef = GetComponent<UMGHealthComponent>();
	if (HealthComponentRef)
	{

			HealthComponentRef->OnHealthChange.AddUObject(this, &UMGPlayerHUDWidget::OnHealthChanged);
			HealthComponentRef->OnDeath.AddUObject(this, &UMGPlayerHUDWidget::OnPlayerDeath);
			UpdateHealth(HealthComponentRef->GetHealthPersent());
	}
	if (WeaponComponentRef)
	{
		WeaponComponentRef->OnWeaponChange.AddUObject(this, &UMGPlayerHUDWidget::OnWeaponChanged);
		WeaponComponentRef->OnWeaponShoot.AddUObject(this, &UMGPlayerHUDWidget::OnWeaponShot);
		UpdateWeapon(WeaponComponentRef->GetCurrentWeapon());
		UpdateAmmo();
	}
	if (SpectatorHUDWidget)
	{
		SpectatorHUDWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMGPlayerHUDWidget::OnHealthChanged(float Health)
{
	if (HealthComponentRef)
	{
		UpdateHealth(HealthComponentRef->GetHealthPersent());
	}
}

void UMGPlayerHUDWidget::OnWeaponChanged(int32 Weapon)
{
	if (WeaponComponentRef)
	{
		UpdateWeapon(Weapon);
		UpdateAmmo();
	}
}

void UMGPlayerHUDWidget::OnWeaponShot(int32 Weapon)
{
	UpdateAmmo();
}

void UMGPlayerHUDWidget::OnPlayerDeath()
{
	const auto Collapsed = ESlateVisibility::Collapsed;
	if (HealthProgressBar) HealthProgressBar->SetVisibility(Collapsed);
	if (AmmoTextBlock) AmmoTextBlock->SetVisibility(Collapsed);
	if (CrossHairImage) CrossHairImage->SetVisibility(Collapsed);
	if (WeaponImage) WeaponImage->SetVisibility(Collapsed);
	if (SpectatorHUDWidget) SpectatorHUDWidget->SetVisibility(ESlateVisibility::Visible);
}
