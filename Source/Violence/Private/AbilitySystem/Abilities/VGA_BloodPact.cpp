// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AbilitySystem/Abilities/VGA_BloodPact.h"

#include "AbilitySystem/VAttributeSet.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "VGameplayTags.h"

UVGA_BloodPact::UVGA_BloodPact()
{
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    SetAssetTags(VGameplayTags::Player_Ability_BloodPact.GetTag().GetSingleTagContainer());
    ActivationBlockedTags.AddTag(VGameplayTags::Player_Ability_BloodPact);
    ActivationOwnedTags.AddTag(VGameplayTags::Player_Status_BloodPactActivation);
    ActivationRequiredTags.AddTag(VGameplayTags::Player_Status_Combat);
}

void UVGA_BloodPact::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
    check(BloodPactMontage);
    ensureAlwaysMsgf(ApplyEffects.Num() > 0, TEXT("BloodPactEffects is empty in %s"), *GetName());

    if (!K2_CommitAbility())
    {
        K2_EndAbility();
        return;
    }

    if (HasAuthorityOrPredictionKey(CurrentActorInfo, &CurrentActivationInfo))
    {
        UAbilityTask_PlayMontageAndWait* PlayBloodPactMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, BloodPactMontage);
        if (PlayBloodPactMontageTask)
        {
            PlayBloodPactMontageTask->OnCompleted.AddDynamic(this, &UVGA_BloodPact::K2_EndAbility);
            PlayBloodPactMontageTask->OnCancelled.AddDynamic(this, &UVGA_BloodPact::K2_EndAbility);
            PlayBloodPactMontageTask->OnBlendOut.AddDynamic(this, &UVGA_BloodPact::K2_EndAbility);
            PlayBloodPactMontageTask->OnInterrupted.AddDynamic(this, &UVGA_BloodPact::K2_EndAbility);
            PlayBloodPactMontageTask->ReadyForActivation();
        }
    }

    if (K2_HasAuthority())
    {
        UAbilityTask_WaitGameplayEvent* WaitBuffAppliedTagEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, VGameplayTags::Player_Event_BuffApplied);
        if (WaitBuffAppliedTagEvent)
        {
            WaitBuffAppliedTagEvent->EventReceived.AddDynamic(this, &UVGA_BloodPact::ApplyBloodPactEffects);
            WaitBuffAppliedTagEvent->ReadyForActivation();
        }
    }
}

void UVGA_BloodPact::ApplyBloodPactEffects(FGameplayEventData EventData)
{
    ClearActiveEffects();

    for (const TSubclassOf<UGameplayEffect>& Effect : ApplyEffects)
    {
        if (!Effect) continue;

        const FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(Effect, GetAbilityLevel(CurrentSpecHandle, CurrentActorInfo));

        FActiveGameplayEffectHandle EffectHandle = ApplyGameplayEffectSpecToOwner(GetCurrentAbilitySpecHandle(), CurrentActorInfo, CurrentActivationInfo,
            EffectSpecHandle);

        ActiveEffects.Add(EffectHandle);
    }
}

void UVGA_BloodPact::ClearActiveEffects()
{
    UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
    if (!ASC) return;

    for (const FActiveGameplayEffectHandle& ActiveEffect : ActiveEffects)
    {
        if (!ActiveEffect.IsValid()) continue;

        ASC->RemoveActiveGameplayEffect(ActiveEffect);
    }

    ActiveEffects.Empty();
}