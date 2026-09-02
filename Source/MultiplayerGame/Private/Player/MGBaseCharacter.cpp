// Multiplayer Game

#include "Player/MGBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY_STATIC(AMGBaseCharacterLog, All, All)

// Sets default values
AMGBaseCharacter::AMGBaseCharacter(const FObjectInitializer &ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<UMGCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need
	// it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void AMGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

bool AMGBaseCharacter::IsRunning() const
{
	UE_LOG(AMGBaseCharacterLog, Display, TEXT("Sprint check: %s"),
		   (IsWantToSprint && IsMovingForward && !GetVelocity().IsZero()) ? TEXT("True") : TEXT("False"));
	return IsWantToSprint && IsMovingForward && !GetVelocity().IsZero();
}

float AMGBaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero())
	{
		return 0.0f;
	}
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

// Called every frame
void AMGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMGBaseCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMGBaseCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMGBaseCharacter::LookAround);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMGBaseCharacter::Jump);
		EnhancedInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &AMGBaseCharacter::SprintStarted);
		EnhancedInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &AMGBaseCharacter::SprintEnded);
	}

	if (const APlayerController *PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem *Subsystem =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}
}

void AMGBaseCharacter::Move(const FInputActionValue &Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	IsMovingForward = MovementVector.Y > 0;
	if (GetController() != nullptr)
	{
		// UE_LOG(AMGBaseCharacterLog, Display, TEXT("MOVE %f,%f"), MovementVector.Y, MovementVector.X);
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMGBaseCharacter::LookAround(const FInputActionValue &Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	// UE_LOG(AMGBaseCharacterLog, Display, TEXT("Look %f,%f"), MovementVector.Y, MovementVector.X);

	if (GetController() != nullptr)
	{
		AddControllerPitchInput(MovementVector.Y);
		AddControllerYawInput(MovementVector.X);
	}
}

void AMGBaseCharacter::SprintStarted()
{
	IsWantToSprint = true;
	UE_LOG(AMGBaseCharacterLog, Display, TEXT("Sprint Wanted: %s"), IsWantToSprint ? TEXT("true") : TEXT("false"));
}

void AMGBaseCharacter::SprintEnded()
{
	IsWantToSprint = false;
	UE_LOG(AMGBaseCharacterLog, Display, TEXT("Sprint ended: %s"), IsWantToSprint ? TEXT("true") : TEXT("false"));
}
