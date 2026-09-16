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
class UWidget;
class UTextBlock;

UCLASS()
class MULTIPLAYERGAME_API UMGPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

  public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateHealth(float HealthPercent);
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetWeaponUIData(FWeaponUIData &UIData) const;
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetWeaponAmmoData(FAmmoData &AmmoData) const;
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerAlive() const;
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerSpectating() const;


  protected:
	virtual void NativeConstruct() override;
	UPROPERTY(meta = (BindWidget))
	UProgressBar *HealthProgressBar;
	UPROPERTY(meta = (BindWidget))
	UImage *CrossHairImage;
	UPROPERTY(meta = (BindWidget))
	UImage *WeaponImage;
	UPROPERTY(meta = (BindWidget))
	UTextBlock *AmmoTextBlock;
	UPROPERTY(meta = (BindWidget))
	UWidget *SpectatorHUDWidget;

  private:
	void UpdateWeapon(int32 Index);
	void UpdateAmmo();
	UPROPERTY()
	UMGHealthComponent *HealthComponentRef;
	UPROPERTY()
	UMGWeaponComponent *WeaponComponentRef;
	void OnHealthChanged(float Health);
	void OnWeaponChanged(int32 Weapon);
	void OnWeaponShot(int32 Weapon);
	void OnPlayerDeath();


};
