// Multiplayer Game

#include "UI/MGPlayerHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/MGHealthComponent.h"
#include "GameFramework/Pawn.h"


void UMGPlayerHUDWidget::UpdateHealth(float HealthPercent)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(HealthPercent);
	}
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
	}
}

void UMGPlayerHUDWidget::OnHealthChanged(float Health)
{
	if (HealthComponentRef)
	{
		UpdateHealth(HealthComponentRef->GetHealthPersent());
	}
}


