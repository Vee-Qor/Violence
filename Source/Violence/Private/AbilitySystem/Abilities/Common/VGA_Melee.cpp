// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AbilitySystem/Abilities/Common//VGA_Melee.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Characters/VCharacter.h"
#include "VGameplayTags.h"

UVGA_Melee::UVGA_Melee()
{
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    ActivationOwnedTags.AddTag(VGameplayTags::Common_Status_Attacking);

    ActivationRequiredTags.AddTag(VGameplayTags::Common_Status_Combat);
    ActivationBlockedTags.AddTag(VGameplayTags::Common_Status_Travel);
    ActivationBlockedTags.AddTag(VGameplayTags::Common_Status_Casting);
    ActivationBlockedTags.AddTag(VGameplayTags::Common_Status_Attacking);
    ActivationBlockedTags.AddTag(VGameplayTags::Common_Status_StanceShifting);
}

void UVGA_Melee::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    check(MeleeAttackMontages.Num() > 0);
    ensureAlwaysMsgf(DamageEffect, TEXT("DamageEffect Empty in %s"), *GetName());

    if (!K2_CommitAbility())
    {
        K2_EndAbility();
        return;
    }

    if (!HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo)) return;

    if (GetWorld() && ComboResetTimerHandle.IsValid())
    {
        GetWorld()->GetTimerManager().ClearTimer(ComboResetTimerHandle);
    }

    if (ComboIndex >= MeleeAttackMontages.Num())
    {
        ResetCombo();
    }

    UAbilityTask_PlayMontageAndWait* PlayPrimaryAttackMontages = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None,
        MeleeAttackMontages[ComboIndex], GetCachedAttackSpeed(), NAME_None, false);
    PlayPrimaryAttackMontages->OnCompleted.AddDynamic(this, &UVGA_Melee::K2_EndAbility);
    PlayPrimaryAttackMontages->OnCancelled.AddDynamic(this, &UVGA_Melee::K2_EndAbility);
    PlayPrimaryAttackMontages->OnBlendOut.AddDynamic(this, &UVGA_Melee::K2_EndAbility);
    PlayPrimaryAttackMontages->OnInterrupted.AddDynamic(this, &UVGA_Melee::K2_EndAbility);
    PlayPrimaryAttackMontages->ReadyForActivation();

    ComboIndex++;

    if (K2_HasAuthority())
    {
        UAbilityTask_WaitGameplayEvent* WaitAttackTraceEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, VGameplayTags::Common_Event_AttackTrace);
        WaitAttackTraceEvent->EventReceived.AddDynamic(this, &UVGA_Melee::AttackTraceEventReceived);
        WaitAttackTraceEvent->ReadyForActivation();
    }

    UAbilityTask_WaitGameplayEvent* WaitCanAttackEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, VGameplayTags::Common_Event_CanAttack);
    WaitCanAttackEvent->EventReceived.AddDynamic(this, &UVGA_Melee::CanAttackTagEventReceived);
    WaitCanAttackEvent->ReadyForActivation();
}

void UVGA_Melee::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    if (AVCharacter* VCharacter = Cast<AVCharacter>(GetAvatarActorFromActorInfo()))
    {
        VCharacter->OnTraceTakeHitResults.RemoveAll(this);
    }

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

    if (GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(ComboResetTimerHandle, this, &UVGA_Melee::ResetCombo, ComboResetDelay, 0.0f);
    }
}

void UVGA_Melee::ResetCombo()
{
    ComboIndex = 0;
}

void UVGA_Melee::AttackTraceEventReceived(FGameplayEventData EventData)
{
    StartTraceTimer(EventData, TraceSphereRadius);

    if (AVCharacter* VCharacter = Cast<AVCharacter>(GetAvatarActorFromActorInfo()))
    {
        VCharacter->OnTraceTakeHitResults.AddUObject(this, &UVGA_Melee::TraceTakeResults);
    }
}

void UVGA_Melee::TraceTakeResults(const TArray<FHitResult>& HitResults) const
{
    ApplyDamageFromHitResults(HitResults, DamageEffect);
}

void UVGA_Melee::CanAttackTagEventReceived(FGameplayEventData EventData)
{
    K2_EndAbility();
}