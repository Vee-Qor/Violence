// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/VGameplayAbility.h"
#include "VGA_StanceShift.generated.h"

UCLASS()
class UVGA_StanceShift : public UVGameplayAbility
{
    GENERATED_BODY()

public:
    UVGA_StanceShift();
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "StanceShift|Animation")
    UAnimMontage* CombatStanceMontage;

    UPROPERTY(EditDefaultsOnly, Category = "StanceShift|Animation")
    UAnimMontage* TravelStanceMontage;

    UPROPERTY()
    UAnimMontage* CurrentStanceMontage;

    UPROPERTY(EditDefaultsOnly, Category = "StanceShift|Effects")
    TSubclassOf<UGameplayEffect> CombatTagEffect;

    UPROPERTY(EditDefaultsOnly, Category = "StanceShift|Effects")
    TSubclassOf<UGameplayEffect> TravelTagEffect;

    void ChooseStanceMontage();

    UFUNCTION()
    void ChangeStanceEventReceived(FGameplayEventData EventData);

    void ChooseStanceMontage();
    void ApplyEffect(UAbilitySystemComponent* AbilitySystemComponent, const TSubclassOf<UGameplayEffect>& EffectToApply,
        const TSubclassOf<UGameplayEffect>& EffectToRemove);
};