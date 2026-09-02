// Multiplayer Game


#include "Player/MGBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

DEFINE_LOG_CATEGORY_STATIC(AMGBaseCharacterLog, All,All)

// Sets default values
AMGBaseCharacter::AMGBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AMGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMGBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMGBaseCharacter::Move(float x, float y)
{
	UE_LOG(AMGBaseCharacterLog, Display, TEXT("Move forward: %f, right %f"), y, x);
	if (GetController() != nullptr)
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, y);
		AddMovementInput(RightDirection, x);
	}
}

