// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/VGameplayAbility.h"
#include "VGA_BloodPact.generated.h"

UCLASS()
class UVGA_BloodPact : public UVGameplayAbility
{
    GENERATED_BODY()

public:
    UVGA_BloodPact();
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData) override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* BloodPactMontage;

    UPROPERTY(EditDefaultsOnly, Category = "BloodPact")
    TArray<TSubclassOf<UGameplayEffect>> ApplyEffects;

    UPROPERTY()
    TArray<FActiveGameplayEffectHandle> ActiveEffects;

    UFUNCTION()
    void ApplyBloodPactEffects(FGameplayEventData EventData);

    void ClearActiveEffects();
};