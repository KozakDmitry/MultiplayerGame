// Multiplayer Game

#include "UI/MGPlayerHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/MGHealthComponent.h"
#include "Components/MGWeaponComponent.h"
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
	}
}

bool UMGPlayerHUDWidget::GetWeaponUIData(FWeaponUIData &UIData) const
{
	if (APawn *Pawn = GetOwningPlayerPawn())
	{
		const auto Component = Pawn->GetComponentByClass(UMGWeaponComponent::StaticClass());
		const auto WeaponComponent = Cast<UMGWeaponComponent>(Component);
		if (!WeaponComponent)
		{
			return false;
		}
		return WeaponComponent->GetWeaponUIData(UIData);
	}
	return false;
}

void UMGPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (APawn *Pawn = GetOwningPlayerPawn())
	{
		HealthComponentRef = Pawn->FindComponentByClass<UMGHealthComponent>();
		if (HealthComponentRef)
		{
			HealthComponentRef->OnHealthChange.AddUObject(this, &UMGPlayerHUDWidget::OnHealthChanged);
			UpdateHealth(HealthComponentRef->GetHealthPersent());
		}
		WeaponComponentRef = Pawn->FindComponentByClass<UMGWeaponComponent>();
		if (WeaponComponentRef)
		{
			WeaponComponentRef->OnWeaponChange.AddUObject(this, &UMGPlayerHUDWidget::OnWeaponChanged);
			UpdateWeapon(WeaponComponentRef->GetCurrentWeapon());
		}
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
	}
}


