// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AbilitySystem/Abilities/Common//VGA_Melee.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "VGameplayTags.h"

UVGA_Melee::UVGA_Melee()
{
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    SetAssetTags(VGameplayTags::Player_Ability_PrimaryAttack.GetTag().GetSingleTagContainer());
    BlockAbilitiesWithTag.AddTag(VGameplayTags::Player_Ability_PrimaryAttack);
    ActivationOwnedTags.AddTag(VGameplayTags::Player_Status_Attacking);
    ActivationBlockedTags.AddTag(VGameplayTags::Player_Status_Travel);
    ActivationBlockedTags.AddTag(VGameplayTags::Player_Status_BloodPactActivation);
    ActivationBlockedTags.AddTag(VGameplayTags::Player_Status_Attacking);
    ActivationRequiredTags.AddTag(VGameplayTags::Player_Status_Combat);
}

void UVGA_Melee::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    check(PrimaryAttackMontages.Num() > 0);
    ensureAlwaysMsgf(DamageEffect, TEXT("DamageEffect Empty in %s"), *GetName());

    if (!K2_CommitAbility())
    {
        K2_EndAbility();
        return;
    }

    if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
    {
        if (GetWorld() && ComboResetTimerHandle.IsValid())
        {
            GetWorld()->GetTimerManager().ClearTimer(ComboResetTimerHandle);
        }

        if (CurrentComboIndex >= PrimaryAttackMontages.Num())
        {
            ResetCombo();
        }

        UAbilityTask_PlayMontageAndWait* PlayPrimaryAttackMontagesTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None,
            PrimaryAttackMontages[CurrentComboIndex], GetCachedAttackSpeed(), NAME_None, false);
        if (PlayPrimaryAttackMontagesTask)
        {
            PlayPrimaryAttackMontagesTask->OnCompleted.AddDynamic(this, &UVGA_PrimaryAttack::K2_EndAbility);
            PlayPrimaryAttackMontagesTask->OnCancelled.AddDynamic(this, &UVGA_PrimaryAttack::K2_EndAbility);
            PlayPrimaryAttackMontagesTask->OnBlendOut.AddDynamic(this, &UVGA_PrimaryAttack::K2_EndAbility);
            PlayPrimaryAttackMontagesTask->OnInterrupted.AddDynamic(this, &UVGA_PrimaryAttack::K2_EndAbility);
            PlayPrimaryAttackMontagesTask->ReadyForActivation();

            CurrentComboIndex++;
        }

        UAbilityTask_WaitGameplayEvent* WaitCanAttackEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, VGameplayTags::Common_Event_CanAttack);
        if (WaitCanAttackEvent)
        {
            WaitCanAttackEvent->EventReceived.AddDynamic(this, &UVGA_Melee::CanAttackTagEventReceived);
            WaitCanAttackEvent->ReadyForActivation();
        }
    }

    if (K2_HasAuthority())
    {
        UAbilityTask_WaitGameplayEvent* WaitAttackTraceEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, VGameplayTags::Common_Event_AttackTrace);
        if (WaitAttackTraceEvent)
        {
            WaitAttackTraceEvent->EventReceived.AddDynamic(this, &UVGA_Melee::AttackTraceEventReceived);
            WaitAttackTraceEvent->ReadyForActivation();
        }
    }
}

void UVGA_Melee::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    OnTraceTakeHitResults.RemoveAll(this);

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

    if (GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(ComboResetTimerHandle, this, &UVGA_Melee::ResetCombo, ComboResetDelay, 0.0f);
    }
}

void UVGA_Melee::ResetCombo()
{
    CurrentComboIndex = 0;
}

void UVGA_Melee::AttackTraceEventReceived(FGameplayEventData EventData)
{
    StartTraceTimer(EventData, TraceSphereRadius);

    OnTraceTakeHitResults.AddUObject(this, &UVGA_Melee::TraceTakeResults);
}

void UVGA_Melee::TraceTakeResults(const TArray<FHitResult>& HitResults) const
{
    ApplyDamageFromHitResults(HitResults, DamageEffect);
}