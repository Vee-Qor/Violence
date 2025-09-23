// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AbilitySystem/Abilities/Common/VGA_HitReact.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "VGameplayTags.h"

UVGA_HitReact::UVGA_HitReact()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerExecution;
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerInitiated;

    FAbilityTriggerData TriggerData;
    TriggerData.TriggerTag = VGameplayTags::Common_Event_Hit_React;
    TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
    AbilityTriggers.Add(TriggerData);
}

void UVGA_HitReact::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    if (!K2_CommitAbility())
    {
        K2_EndAbility();
        return;
    }

    SelectHitReactMontage(*TriggerEventData);

    if (SelectedHitReactMontage)
    {
        UAbilityTask_PlayMontageAndWait* PlaySelectedHitReactMontage = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None,
            SelectedHitReactMontage);
        if (PlaySelectedHitReactMontage)
        {
            PlaySelectedHitReactMontage->OnCompleted.AddDynamic(this, &UVGA_HitReact::K2_EndAbility);
            PlaySelectedHitReactMontage->OnCancelled.AddDynamic(this, &UVGA_HitReact::K2_EndAbility);
            PlaySelectedHitReactMontage->OnBlendOut.AddDynamic(this, &UVGA_HitReact::K2_EndAbility);
            PlaySelectedHitReactMontage->OnInterrupted.AddDynamic(this, &UVGA_HitReact::K2_EndAbility);
            PlaySelectedHitReactMontage->ReadyForActivation();
        }
    }

}

void UVGA_HitReact::SelectHitReactMontage(const FGameplayEventData& TriggerEventData)
{
    const AActor* AvatarActor = GetAvatarActorFromActorInfo();
    const FHitResult* HitResult = TriggerEventData.ContextHandle.GetHitResult();
    const AActor* HitActor = HitResult->GetActor();
    if (!HitActor || HitActor != AvatarActor) return;

    FVector ImpactDirection = HitResult->ImpactPoint - HitActor->GetActorLocation();
    ImpactDirection.Z = 0.0f;
    ImpactDirection = AvatarActor->GetActorTransform().InverseTransformVector(ImpactDirection);
    ImpactDirection.Normalize();

    const FVector Forward(1.0f, 0.0f, 0.0f);
    const FVector Right(0.0f, 1.0f, 0.0f);

    const float DotForward = FVector::DotProduct(ImpactDirection, Forward);
    const float DotRight = FVector::DotProduct(ImpactDirection, Right);

    EVHitReactSides LocalSide = EVHitReactSides::Front;

    if (FMath::Abs(DotForward) > FMath::Abs(DotRight))
    {
        LocalSide = (DotForward > 0.0f) ? EVHitReactSides::Front : EVHitReactSides::Back;
    }
    else
    {
        LocalSide = (DotRight > 0.0f) ? EVHitReactSides::Right : EVHitReactSides::Left;
    }

    SelectedHitReactMontage = HitReactMap.FindRef(LocalSide);
}