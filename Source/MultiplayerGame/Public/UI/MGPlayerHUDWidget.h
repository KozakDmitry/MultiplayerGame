// Multiplayer Game

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "MGPlayerHUDWidget.generated.h"

class UMGHealthComponent;
class UProgressBar;

UCLASS()
class MULTIPLAYERGAME_API UMGPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

  public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateHealth(float HealthPercent);

  protected:
	virtual void NativeConstruct() override;
	UPROPERTY(meta = (BindWidget))
	UProgressBar *HealthProgressBar;

  private:
	UPROPERTY()
	UMGHealthComponent *HealthComponentRef;
	void OnHealthChanged(float Health);
};
