// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AbilitySystem/Abilities/VGA_PrimaryAttack.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "VGameplayTags.h"

UVGA_PrimaryAttack::UVGA_PrimaryAttack()
{
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    SetAssetTags(VGameplayTags::Player_Ability_PrimaryAttack.GetTag().GetSingleTagContainer());
    BlockAbilitiesWithTag.AddTag(VGameplayTags::Player_Ability_PrimaryAttack);
    ActivationOwnedTags.AddTag(VGameplayTags::Player_Status_Attacking);
}

void UVGA_PrimaryAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    check(PrimaryAttackMontages.Num() > 0);

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
            PrimaryAttackMontages[CurrentComboIndex]);
        if (PlayPrimaryAttackMontagesTask)
        {
            PlayPrimaryAttackMontagesTask->OnCompleted.AddDynamic(this, &UVGA_PrimaryAttack::K2_EndAbility);
            PlayPrimaryAttackMontagesTask->OnCancelled.AddDynamic(this, &UVGA_PrimaryAttack::K2_EndAbility);
            PlayPrimaryAttackMontagesTask->OnBlendOut.AddDynamic(this, &UVGA_PrimaryAttack::K2_EndAbility);
            PlayPrimaryAttackMontagesTask->OnInterrupted.AddDynamic(this, &UVGA_PrimaryAttack::K2_EndAbility);
            PlayPrimaryAttackMontagesTask->ReadyForActivation();

            CurrentComboIndex++;
        }
    }

    if (K2_HasAuthority())
    {
        UAbilityTask_WaitGameplayEvent* WaitTraceEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, VGameplayTags::Player_Event_SwordTrace);
        if (WaitTraceEvent)
        {
            WaitTraceEvent->EventReceived.AddDynamic(this, &UVGA_PrimaryAttack::TraceEventReceived);
            WaitTraceEvent->ReadyForActivation();
        }
    }
}

void UVGA_PrimaryAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    OnTraceTakeHitResults.RemoveAll(this);

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

    if (GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(ComboResetTimerHandle, this, &UVGA_PrimaryAttack::ResetCombo, ComboResetDelay, 0.0f);
    }
}

void UVGA_PrimaryAttack::ResetCombo()
{
    CurrentComboIndex = 0;
}

void UVGA_PrimaryAttack::TraceEventReceived(FGameplayEventData EventData)
{
    StartTraceTimer(EventData, TraceSphereRadius);

    OnTraceTakeHitResults.AddUObject(this, &UVGA_PrimaryAttack::TraceTakeResults);
}

void UVGA_PrimaryAttack::TraceTakeResults(const TArray<FHitResult>& HitResults) const
{
    ApplyDamageFromHitResults(HitResults, DamageEffect);
}