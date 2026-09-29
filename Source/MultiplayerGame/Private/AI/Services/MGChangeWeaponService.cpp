// Multiplayer Game

#include "AI/Services/MGChangeWeaponService.h"
#include "AIController.h"
#include "Components/MGAIWeaponComponent.h"
#include "MGUtils.h"

UMGChangeWeaponService::UMGChangeWeaponService()
{
	NodeName = "Change Weapon";
}

void UMGChangeWeaponService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (Controller)
	{
		const auto WeaponComponent = MGUtils::GetComponent<UMGAIWeaponComponent>(Controller->GetPawn());
		if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
		{
			WeaponComponent->NextWeapon();
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
