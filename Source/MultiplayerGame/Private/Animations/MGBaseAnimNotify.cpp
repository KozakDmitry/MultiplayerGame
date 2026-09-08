// Multiplayer Game


#include "Animations/MGBaseAnimNotify.h"

void UMGBaseAnimNotify::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation,
						   const FAnimNotifyEventReference &EventReference)
{

	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation, EventReference);
}
