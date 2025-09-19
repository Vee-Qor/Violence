// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AbilitySystem/Abilities/VGA_AirSlash.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "VGameplayTags.h"

UVGA_AirSlash::UVGA_AirSlash()
{
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    SetAssetTags(VGameplayTags::Player_Ability_AirSlash.GetTag().GetSingleTagContainer());
    ActivationOwnedTags.AddTag(VGameplayTags::Player_Status_Attacking);
    BlockAbilitiesWithTag.AddTag(VGameplayTags::Player_Ability_AirSlash);
    ActivationBlockedTags.AddTag(VGameplayTags::Player_Status_Travel);
    ActivationBlockedTags.AddTag(VGameplayTags::Player_Status_BloodPactActivation);
    ActivationBlockedTags.AddTag(VGameplayTags::Player_Status_Attacking);
    ActivationRequiredTags.AddTag(VGameplayTags::Player_Status_InAir);
    ActivationRequiredTags.AddTag(VGameplayTags::Player_Status_Combat);
}

void UVGA_AirSlash::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    check(AirSlashMontage);
    ensureAlwaysMsgf(DamageEffect, TEXT("DamageEffect Empty in %s"), *GetName());

    if (!K2_CommitAbility())
    {
        K2_EndAbility();
        return;
    }

    if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
    {
        UAbilityTask_PlayMontageAndWait* PlayAirSlashMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, AirSlashMontage,
            GetCachedAttackSpeed(), NAME_None, false);
        if (PlayAirSlashMontageTask)
        {
            PlayAirSlashMontageTask->OnCompleted.AddDynamic(this, &UVGA_AirSlash::K2_EndAbility);
            PlayAirSlashMontageTask->OnCancelled.AddDynamic(this, &UVGA_AirSlash::K2_EndAbility);
            PlayAirSlashMontageTask->OnBlendOut.AddDynamic(this, &UVGA_AirSlash::K2_EndAbility);
            PlayAirSlashMontageTask->OnInterrupted.AddDynamic(this, &UVGA_AirSlash::K2_EndAbility);
            PlayAirSlashMontageTask->ReadyForActivation();
        }

        UAbilityTask_WaitGameplayEvent* WaitCanAttackTagEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, VGameplayTags::Player_Event_CanAttack);
        if (WaitCanAttackTagEvent)
        {
            WaitCanAttackTagEvent->EventReceived.AddDynamic(this, &UVGA_AirSlash::CanAttackTagEventReceived);
            WaitCanAttackTagEvent->ReadyForActivation();
        }
    }

    if (K2_HasAuthority())
    {
        UAbilityTask_WaitGameplayEvent* WaitTraceEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, VGameplayTags::Player_Event_SwordTrace);
        WaitTraceEvent->EventReceived.AddDynamic(this, &UVGA_AirSlash::TraceEventReceived);
        WaitTraceEvent->ReadyForActivation();
    }
}

void UVGA_AirSlash::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
    bool bReplicateEndAbility, bool bWasCancelled)
{
    OnTraceTakeHitResults.RemoveAll(this);

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UVGA_AirSlash::TraceEventReceived(FGameplayEventData EventData)
{
    StartTraceTimer(EventData, TraceSphereRadius);

    OnTraceTakeHitResults.AddUObject(this, &UVGA_AirSlash::TraceTakeResults);
}

void UVGA_AirSlash::TraceTakeResults(const TArray<FHitResult>& HitResults) const
{
    if (HitResults.IsEmpty()) return;

    ApplyDamageFromHitResults(HitResults, DamageEffect);
}