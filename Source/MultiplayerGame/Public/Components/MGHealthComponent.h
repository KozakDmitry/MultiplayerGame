// Multiplayer Game

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "MGHealthComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(ForHealthChange,float)

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MULTIPLAYERGAME_API UMGHealthComponent : public UActorComponent
{
	GENERATED_BODY()

  public:
	UMGHealthComponent();
	float GetHealth() const
	{
		return Health;
	}

	UFUNCTION(BlueprintCallable)
	bool IsDead() const
	{
		return FMath::IsNearlyEqual(Health, 0);
	}

	FOnDeath OnDeath;
	ForHealthChange OnHealthChange;


  protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	bool AutoHeal = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health",
			  meta = (EditCondition = "AutoHeal", ClampMin = "0", ClampMax = "10"))
	float HealUpdateTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health",
			  meta = (EditCondition = "AutoHeal", ClampMin = "0", ClampMax = "10"))
	float RegenerationHealModifier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health",
			  meta = (EditCondition = "AutoHeal", ClampMin = "0", ClampMax = "10"))
	float RegenerationDelay;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health",
			  meta = (EditCondition = "AutoHeal", ClampMin = "0", ClampMax = "1000"))
	float MaxHealth = 100;

  private:
	float Health = 0;

	FTimerHandle RegenerationTimerHandle;
	
	UFUNCTION()
	void OnTakeAnyDamageHandle(AActor *OnTakeDamage, float Damage, const class UDamageType *DamageType,
							   class AController *InstigatedBy, AActor *DamageCauser);

	void HealUpdate();
	void SetHealth(float newHealth);

};
