// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AbilitySystem/Abilities/VGA_PrimaryAttack.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "VGameplayTags.h"

UVGA_PrimaryAttack::UVGA_PrimaryAttack()
{
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    SetAssetTags(VGameplayTags::Player_Ability_PrimaryAttack.GetTag().GetSingleTagContainer());

    BlockAbilitiesWithTag.AddTag(VGameplayTags::Player_Ability_PrimaryAttack);
    BlockAbilitiesWithTag.AddTag(VGameplayTags::Player_Status_InAir);

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
        if (GetWorld() && ResetCurrentAttackCountTimerHandle.IsValid())
        {
            GetWorld()->GetTimerManager().ClearTimer(ResetCurrentAttackCountTimerHandle);
        }

        if (CurrentAttackCount >= PrimaryAttackMontages.Num())
        {
            ResetCurrentAttackCount();
        }

        UAbilityTask_PlayMontageAndWait* PlayPrimaryAttackMontagesTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None,
            PrimaryAttackMontages[CurrentAttackCount]);
        PlayPrimaryAttackMontagesTask->OnCompleted.AddDynamic(this, &UVGA_PrimaryAttack::K2_EndAbility);
        PlayPrimaryAttackMontagesTask->OnCancelled.AddDynamic(this, &UVGA_PrimaryAttack::K2_EndAbility);
        PlayPrimaryAttackMontagesTask->OnBlendOut.AddDynamic(this, &UVGA_PrimaryAttack::K2_EndAbility);
        PlayPrimaryAttackMontagesTask->OnInterrupted.AddDynamic(this, &UVGA_PrimaryAttack::K2_EndAbility);
        PlayPrimaryAttackMontagesTask->ReadyForActivation();

        CurrentAttackCount++;
    }
}

void UVGA_PrimaryAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

    if (GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(ResetCurrentAttackCountTimerHandle, this, &UVGA_PrimaryAttack::ResetCurrentAttackCount, ResetAttackCountTimeDuration,
            0.0f);
    }
}

void UVGA_PrimaryAttack::ResetCurrentAttackCount()
{
    CurrentAttackCount = 0;
}