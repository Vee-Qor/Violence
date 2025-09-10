// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/VGameplayAbility.h"
#include "VGA_PrimaryAttack.generated.h"

UCLASS()
class UVGA_PrimaryAttack : public UVGameplayAbility
{
    GENERATED_BODY()

public:
    UVGA_PrimaryAttack();
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
        bool bReplicateEndAbility, bool bWasCancelled) override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    TArray<UAnimMontage*> PrimaryAttackMontages;

    UPROPERTY(EditDefaultsOnly, Category = "Primary Attack")
    int32 CurrentAttackCount = 0;

    UPROPERTY(EditDefaultsOnly, Category = "Primary Attack")
    float ResetAttackCountTimeDuration = 0.5f;

    FTimerHandle ResetCurrentAttackCountTimerHandle;
    void ResetCurrentAttackCount();
};