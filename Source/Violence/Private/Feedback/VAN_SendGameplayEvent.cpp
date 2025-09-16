// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "Feedback/VAN_SendGameplayEvent.h"

#include "AbilitySystemBlueprintLibrary.h"

void UVAN_SendGameplayEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    if (!MeshComp || !MeshComp->GetOwner()) return;

    AActor* Owner = MeshComp->GetOwner();
    if (!Owner) return;

    if (!UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Owner)) return;

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner, EventTag, FGameplayEventData{});
}