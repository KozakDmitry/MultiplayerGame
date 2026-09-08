// Multiplayer Game

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "MGBaseAnimNotify.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, USkeletalMeshComponent *)

	/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API UMGBaseAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

	  public:
	virtual void Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation,
						const FAnimNotifyEventReference &EventReference) override;
	FOnNotifiedSignature OnNotified;
	
};
