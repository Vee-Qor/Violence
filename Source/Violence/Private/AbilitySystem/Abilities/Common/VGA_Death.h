// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/VGameplayAbility.h"
#include "VGA_Death.generated.h"

UCLASS()
class UVGA_Death : public UVGameplayAbility
{
    GENERATED_BODY()

public:
    UVGA_Death();
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Death|Animation")
    TArray<UAnimMontage*> DeathMontages;

    UPROPERTY(EditDefaultsOnly, Category = "Death|Effects")
    TSubclassOf<UGameplayEffect> DeathEffect;

    UPROPERTY(EditDefaultsOnly, Category = "Death|VFX", meta = (Categories = "GameplayCue"))
    FGameplayTag DeathDissolveCueTag;

    UPROPERTY(Transient)
    UAnimMontage* SelectedDeathMontage;

    void SelectDeathMontage();
    void ApplyDeathState();

    UFUNCTION()
    void EndDeath();
};