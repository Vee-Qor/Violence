// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "Feedback/VANS_SendCanAttackWindow.h"

#include "AbilitySystemBlueprintLibrary.h"

void UVANS_SendCanAttackWindow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
    const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

    if (!MeshComp || !MeshComp->GetOwner()) return;

    if (!UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(MeshComp->GetOwner())) return;

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), CanAttackTag, FGameplayEventData{});
}

void UVANS_SendCanAttackWindow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyEnd(MeshComp, Animation, EventReference);

    if (!MeshComp || !MeshComp->GetOwner()) return;

    if (!UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(MeshComp->GetOwner())) return;

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), ResetAttackTag, FGameplayEventData{});
}