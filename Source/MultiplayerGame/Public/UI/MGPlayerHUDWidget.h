// Multiplayer Game

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "MGCoreTypes.h"
#include "MGPlayerHUDWidget.generated.h"

class UMGHealthComponent;
class UMGWeaponComponent;
class UProgressBar;
class UImage;

UCLASS()
class MULTIPLAYERGAME_API UMGPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

  public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateHealth(float HealthPercent);
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetWeaponUIData(FWeaponUIData &UIData) const;

  protected:
	virtual void NativeConstruct() override;
	UPROPERTY(meta = (BindWidget))
	UProgressBar *HealthProgressBar;
	UPROPERTY(meta = (BindWidget))
	UImage *CrossHairImage;

  private:
	void UpdateWeapon(int32 Index);
	UPROPERTY()
	UMGHealthComponent *HealthComponentRef;
	UPROPERTY()
	UMGWeaponComponent *WeaponComponentRef;
	void OnHealthChanged(float Health);
	void OnWeaponChanged(int32 Weapon);
};
