// Multiplayer Game

#include "Components/MGHealthComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(MGHealthComponentLog, All, All)
// Sets default values for this component's properties
UMGHealthComponent::UMGHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these
	// features off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UMGHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	SetHealth(MaxHealth);

	AActor *ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UMGHealthComponent::OnTakeAnyDamageHandle);
	}
}

void UMGHealthComponent::OnTakeAnyDamageHandle(AActor *OnTakeDamage, float Damage, const UDamageType *DamageType,
											   AController *InstigatedBy, AActor *DamageCauser)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld())
	{
		return;
	}
	SetHealth(Health - Damage);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if (AutoHeal && GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(RegenerationTimerHandle, this, &UMGHealthComponent::HealUpdate, HealUpdateTime, true, RegenerationDelay);
	}
	// UE_LOG(MGHealthComponentLog, Display, TEXT("Damage: %f"), Damage);
}

void UMGHealthComponent::HealUpdate()
{
	SetHealth(Health + RegenerationHealModifier);
	if (FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(RegenerationTimerHandle);
	}
}

void UMGHealthComponent::SetHealth(float newHealth)
{
	Health = FMath::Clamp(newHealth, 0.0f, MaxHealth);
	OnHealthChange.Broadcast(Health);
}



// Called every frame
