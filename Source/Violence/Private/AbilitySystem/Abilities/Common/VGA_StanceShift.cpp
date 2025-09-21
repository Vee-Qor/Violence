// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AbilitySystem/Abilities/Common/VGA_StanceShift.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "VGameplayTags.h"

UVGA_StanceShift::UVGA_StanceShift()
{
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    SetAssetTags(VGameplayTags::Player_Ability_StanceShift.GetTag().GetSingleTagContainer());
    BlockAbilitiesWithTag.AddTag(VGameplayTags::Player_Ability_StanceShift);
    ActivationOwnedTags.AddTag(VGameplayTags::Player_Status_StanceShifting);
}

void UVGA_StanceShift::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    check(CombatStanceMontage);
    check(TravelStanceMontage);
    ensureAlwaysMsgf(CombatTagEffect, TEXT("CombatTagEffect Empty in %s"), *GetName());
    ensureAlwaysMsgf(TravelTagEffect, TEXT("TravelTagEffect Empty in %s"), *GetName());

    if (!K2_CommitAbility())
    {
        K2_EndAbility();
        return;
    }

    if (!HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo)) return;

    ChooseStanceMontage();

    UAbilityTask_PlayMontageAndWait* PlayEquipMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, CurrentStanceMontage);
    if (PlayEquipMontageTask)
    {
        PlayEquipMontageTask->OnCompleted.AddDynamic(this, &UVGA_StanceShift::K2_EndAbility);
        PlayEquipMontageTask->OnCancelled.AddDynamic(this, &UVGA_StanceShift::K2_EndAbility);
        PlayEquipMontageTask->OnBlendOut.AddDynamic(this, &UVGA_StanceShift::K2_EndAbility);
        PlayEquipMontageTask->OnInterrupted.AddDynamic(this, &UVGA_StanceShift::K2_EndAbility);
        PlayEquipMontageTask->ReadyForActivation();
    }

    UAbilityTask_WaitGameplayEvent* WaitChangeStanceEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, VGameplayTags::Common_Event_StanceShift);
    if (WaitChangeStanceEvent)
    {
        WaitChangeStanceEvent->EventReceived.AddDynamic(this, &UVGA_StanceShift::ChangeStanceEventReceived);
        WaitChangeStanceEvent->ReadyForActivation();
    }
}

void UVGA_StanceShift::ChooseStanceMontage()
{
    const UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
    if (!ASC) return;

    if (ASC->HasMatchingGameplayTag(VGameplayTags::Common_Status_Combat))
    {
        CurrentStanceMontage = TravelStanceMontage;
    }
    else if (ASC->HasMatchingGameplayTag(VGameplayTags::Common_Status_Travel))
    {
        CurrentStanceMontage = CombatStanceMontage;
    }
}

void UVGA_StanceShift::ChangeStanceEventReceived(FGameplayEventData EventData)
{
    UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
    if (!ASC) return;

    if (ASC->HasMatchingGameplayTag(VGameplayTags::Common_Status_Combat))
    {
        ApplyEffect(ASC, TravelTagEffect, CombatTagEffect);
    }
    else if (ASC->HasMatchingGameplayTag(VGameplayTags::Common_Status_Travel))
    {
        ApplyEffect(ASC, CombatTagEffect, TravelTagEffect);
    }
}

void UVGA_StanceShift::ApplyEffect(UAbilitySystemComponent* ASC, const TSubclassOf<UGameplayEffect>& EffectToApply,
    const TSubclassOf<UGameplayEffect>& EffectToRemove)
{
    if (!K2_HasAuthority() || !ASC) return;

    ASC->RemoveActiveGameplayEffectBySourceEffect(EffectToRemove, nullptr);
    BP_ApplyGameplayEffectToOwner(EffectToApply, 1);
}