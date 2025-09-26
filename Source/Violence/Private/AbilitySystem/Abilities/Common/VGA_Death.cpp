// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AbilitySystem/Abilities/Common/VGA_Death.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "BrainComponent.h"
#include "Characters/VCharacter.h"
#include "Controllers/VAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "VGameplayTags.h"

UVGA_Death::UVGA_Death()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerInitiated;

    SetAssetTags(VGameplayTags::Common_Ability_Death.GetTag().GetSingleTagContainer());
    CancelAbilitiesWithTag.AddTag(VGameplayTags::Common_Ability_Hit_React);

    FAbilityTriggerData TriggerData;
    TriggerData.TriggerTag = VGameplayTags::Common_Event_Death;
    TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
    AbilityTriggers.Add(TriggerData);
}

void UVGA_Death::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    check(DeathMontages.Num() > 0);
    ensureAlwaysMsgf(DeathEffect, TEXT("DeathEffect is empty in: %s"), *GetName());
    ensureAlwaysMsgf(DeathDissolveCueTag.IsValid(), TEXT("DeathDissolveCueTag is empty in: %s "), *GetName());

    if (!K2_CommitAbility())
    {
        K2_EndAbility();
        return;
    }

    SelectDeathMontage();

    if (SelectedDeathMontage)
    {
        ApplyDeathState();

        UAbilityTask_PlayMontageAndWait* PlayDeathMontage = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None,
            SelectedDeathMontage);
        PlayDeathMontage->OnCompleted.AddDynamic(this, &UVGA_Death::EndDeath);
        PlayDeathMontage->OnCancelled.AddDynamic(this, &UVGA_Death::EndDeath);
        PlayDeathMontage->OnBlendOut.AddDynamic(this, &UVGA_Death::EndDeath);
        PlayDeathMontage->OnInterrupted.AddDynamic(this, &UVGA_Death::EndDeath);
        PlayDeathMontage->ReadyForActivation();
    }

}

void UVGA_Death::SelectDeathMontage()
{
    const int32 RandomMontageIndex = FMath::RandRange(0, DeathMontages.Num() - 1);
    SelectedDeathMontage = DeathMontages[RandomMontageIndex];
    if (!SelectedDeathMontage)
    {
        K2_EndAbility();
    }
}

void UVGA_Death::ApplyDeathState()
{
    if (K2_HasAuthority())
    {
        UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
        if (!ASC) return;

        ASC->BP_ApplyGameplayEffectToSelf(DeathEffect, GetAbilityLevel(CurrentSpecHandle, CurrentActorInfo), ASC->MakeEffectContext());
    }

    ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo());
    if (!Character) return;

    Character->GetCharacterMovement()->DisableMovement();
    Character->GetCharacterMovement()->StopMovementImmediately();

    if (APlayerController* PlayerController = Character->GetController<APlayerController>())
    {
        Character->DisableInput(PlayerController);
    }

    const AVAIController* VAIController = Character->GetController<AVAIController>();
    if (!VAIController || !VAIController->GetBrainComponent()) return;

    VAIController->GetBrainComponent()->StopLogic("Dead");
    VAIController->SetAllSenseEnabled(false);
}

void UVGA_Death::EndDeath()
{
    if (AVCharacter* VCharacter = GetVCharacterFromActorInfo())
    {
        VCharacter->SetRagdollState(true);
    }

    K2_ExecuteGameplayCue(DeathDissolveCueTag, MakeEffectContext(CurrentSpecHandle, CurrentActorInfo));
    
    K2_EndAbility();
}