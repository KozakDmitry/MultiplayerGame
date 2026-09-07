// Multiplayer Game


#include "Animations/MGAnimNotify.h"

void UMGAnimNotify::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation,
						   const FAnimNotifyEventReference &EventReference)
{

	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation, EventReference);
}
