// Multiplayer Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/MGCharacterMovementComponent.h"
#include "MGBaseCharacter.generated.h"

class UInputMappingContext;
struct FInputActionValue;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class MULTIPLAYERGAME_API AMGBaseCharacter : public ACharacter
{
	GENERATED_BODY()

  public:
	// Sets default values for this character's properties
	AMGBaseCharacter(const FObjectInitializer& ObjInit);

  protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent *SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent *CameraComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")

	UInputMappingContext *InputMapping;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> ShiftAction;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

  public:
	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsRunning() const;
	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

  private:
	bool IsWantToSprint;
	bool IsMovingForward;
	void Move(const FInputActionValue &Value);

	void LookAround(const FInputActionValue &Value);
	void SprintStarted();
	void SprintEnded();
	;
};
