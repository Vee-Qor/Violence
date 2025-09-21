// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AbilitySystem/Abilities/Common//VGA_Buff.h"

#include "AbilitySystem/VAttributeSet.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "VGameplayTags.h"

UVGA_Buff::UVGA_Buff()
{
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    ActivationOwnedTags.AddTag(VGameplayTags::Common_Status_Casting);

    ActivationRequiredTags.AddTag(VGameplayTags::Common_Status_Combat);
    ActivationBlockedTags.AddTag(VGameplayTags::Common_Status_Travel);
    ActivationBlockedTags.AddTag(VGameplayTags::Common_Status_Casting);
    ActivationBlockedTags.AddTag(VGameplayTags::Common_Status_Attacking);
    ActivationBlockedTags.AddTag(VGameplayTags::Common_Status_StanceShifting);
}

void UVGA_Buff::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
    check(BuffMontage);
    ensureAlwaysMsgf(ApplyEffects.Num() > 0, TEXT("ApplyEffects is empty in %s"), *GetName());

    if (!K2_CommitAbility())
    {
        K2_EndAbility();
        return;
    }

    if (HasAuthorityOrPredictionKey(CurrentActorInfo, &CurrentActivationInfo))
    {
        UAbilityTask_PlayMontageAndWait* PlayBuffMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, BuffMontage);
        if (PlayBuffMontageTask)
        {
            PlayBuffMontageTask->OnCompleted.AddDynamic(this, &UVGA_Buff::K2_EndAbility);
            PlayBuffMontageTask->OnCancelled.AddDynamic(this, &UVGA_Buff::K2_EndAbility);
            PlayBuffMontageTask->OnBlendOut.AddDynamic(this, &UVGA_Buff::K2_EndAbility);
            PlayBuffMontageTask->OnInterrupted.AddDynamic(this, &UVGA_Buff::K2_EndAbility);
            PlayBuffMontageTask->ReadyForActivation();
        }
    }

    if (K2_HasAuthority())
    {
        UAbilityTask_WaitGameplayEvent* WaitBuffAppliedTagEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this,
            VGameplayTags::Common_Event_BuffApplied);
        if (WaitBuffAppliedTagEvent)
        {
            WaitBuffAppliedTagEvent->EventReceived.AddDynamic(this, &UVGA_Buff::ApplyBuffEffects);
            WaitBuffAppliedTagEvent->ReadyForActivation();
        }
    }
}

void UVGA_Buff::ApplyBuffEffects(FGameplayEventData EventData)
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

void UVGA_Buff::ClearActiveEffects()
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