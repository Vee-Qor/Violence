// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AbilitySystem/Abilities/Common/VGA_Respawn.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "BrainComponent.h"
#include "Characters/VCharacter.h"
#include "Controllers/VAIController.h"
#include "VGameplayTags.h"

UVGA_Respawn::UVGA_Respawn()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerInitiated;

    SetAssetTags(VGameplayTags::Common_Ability_Respawn.GetTag().GetSingleTagContainer());

    FAbilityTriggerData TriggerData;
    TriggerData.TriggerTag = VGameplayTags::Common_Event_Respawn;
    TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
    AbilityTriggers.Add(TriggerData);
}

void UVGA_Respawn::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
    check(RespawnMontage);

    if (!K2_CommitAbility())
    {
        K2_EndAbility();
        return;
    }

    ApplyRespawnState();

    UAbilityTask_PlayMontageAndWait* PlayRespawnMontage = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, RespawnMontage);
    PlayRespawnMontage->OnCompleted.AddDynamic(this, &UVGA_Respawn::EnableInput);
    PlayRespawnMontage->OnCancelled.AddDynamic(this, &UVGA_Respawn::EnableInput);
    PlayRespawnMontage->OnBlendOut.AddDynamic(this, &UVGA_Respawn::EnableInput);
    PlayRespawnMontage->OnInterrupted.AddDynamic(this, &UVGA_Respawn::EnableInput);
    PlayRespawnMontage->ReadyForActivation();
}

void UVGA_Respawn::ApplyRespawnState()
{
    if (K2_HasAuthority())
    {
        UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
        if (!ASC) return;
        ASC->BP_ApplyGameplayEffectToSelf(RespawnEffect, 1, ASC->MakeEffectContext());
        ASC->RemoveActiveGameplayEffectBySourceEffect(DeadEffectToRemove, ASC);
    }

    FGameplayCueParameters CueParams;
    CueParams.RawMagnitude = DissolveDuration;
    CueParams.EffectContext = MakeEffectContext(CurrentSpecHandle, CurrentActorInfo);
    K2_ExecuteGameplayCueWithParams(RespawnDissolveCueTag, CueParams);

    AVCharacter* VCharacter = GetVCharacterFromActorInfo();
    if (!VCharacter) return;

    VCharacter->SetRagdollState(false);
}

void UVGA_Respawn::EnableInput()
{
    if (AVCharacter* VCharacter = GetVCharacterFromActorInfo())
    {
        if (APlayerController* PlayerController = VCharacter->GetController<APlayerController>())
        {
            VCharacter->EnableInput(PlayerController);
        }

        const AVAIController* VAIController = VCharacter->GetController<AVAIController>();
        if (VAIController && VAIController->GetBrainComponent())
        {
            VAIController->GetBrainComponent()->StartLogic();
        }
    }

    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}