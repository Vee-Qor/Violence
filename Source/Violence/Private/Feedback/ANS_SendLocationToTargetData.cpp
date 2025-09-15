// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "Feedback/ANS_SendLocationToTargetData.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void UANS_SendLocationToTargetData::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
    const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

    if (!MeshComp || !MeshComp->GetOwner()) return;

    if (!UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(MeshComp->GetOwner())) return;

    TArray<FName> ActiveSockets;
    switch (WeaponHand)
    {
        case EWeaponHand::Right: ActiveSockets.Add(RightSocketName);
            break;
        case EWeaponHand::Left: ActiveSockets.Add(LeftSocketName);
            break;
        case EWeaponHand::Both: ActiveSockets.Add(RightSocketName);
            ActiveSockets.Add(LeftSocketName);
            break;
    }

    FGameplayEventData EventData;

    for (const FName& SocketName : ActiveSockets)
    {
        FGameplayAbilityTargetData_SingleTargetHit* HitData = new FGameplayAbilityTargetData_SingleTargetHit;
        HitData->HitResult.MyBoneName = SocketName;
        EventData.TargetData.Add(HitData);
    }

    FGameplayAbilityTargetData_SingleTargetHit* HitData = new FGameplayAbilityTargetData_SingleTargetHit;
    HitData->HitResult.ElementIndex = MaxTraces;
    EventData.TargetData.Add(HitData);
    EventData.EventMagnitude = TotalDuration;

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), EventTag, EventData);
}