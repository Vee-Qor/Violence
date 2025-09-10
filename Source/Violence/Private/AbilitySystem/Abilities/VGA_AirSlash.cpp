// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AbilitySystem/Abilities/VGA_AirSlash.h"

#include "VGameplayTags.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

UVGA_AirSlash::UVGA_AirSlash()
{
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    SetAssetTags(VGameplayTags::Player_Ability_AirSlash.GetTag().GetSingleTagContainer());
    ActivationOwnedTags.AddTag(VGameplayTags::Player_Status_Attacking);
    BlockAbilitiesWithTag.AddTag(VGameplayTags::Player_Ability_AirSlash);
    BlockAbilitiesWithTag.AddTag(VGameplayTags::Player_Ability_PrimaryAttack);
    ActivationRequiredTags.AddTag(VGameplayTags::Player_Status_InAir);
}

void UVGA_AirSlash::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    if (!K2_CommitAbility())
    {
        K2_EndAbility();
        return;
    }

    if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
    {
        UAbilityTask_PlayMontageAndWait* PlayAirSlashMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, AirSlashMontage);
        if (PlayAirSlashMontageTask)
        {
            PlayAirSlashMontageTask->OnCompleted.AddDynamic(this, &UVGA_AirSlash::K2_EndAbility);
            PlayAirSlashMontageTask->OnCancelled.AddDynamic(this, &UVGA_AirSlash::K2_EndAbility);
            PlayAirSlashMontageTask->OnBlendOut.AddDynamic(this, &UVGA_AirSlash::K2_EndAbility);
            PlayAirSlashMontageTask->OnInterrupted.AddDynamic(this, &UVGA_AirSlash::K2_EndAbility);
            PlayAirSlashMontageTask->ReadyForActivation();
        }
    }
}