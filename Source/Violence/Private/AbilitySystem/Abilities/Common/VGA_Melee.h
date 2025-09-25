// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/VGameplayAbility.h"
#include "VGA_Melee.generated.h"

UCLASS()
class UVGA_Melee : public UVGameplayAbility
{
    GENERATED_BODY()

public:
    UVGA_Melee();
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Melee|Animation")
    TArray<UAnimMontage*> MeleeAttackMontages;

    UPROPERTY(EditDefaultsOnly, Category = "Melee|Damage")
    TSubclassOf<UGameplayEffect> DamageEffect;

    UPROPERTY(EditDefaultsOnly, Category = "Melee|Trace")
    float TraceSphereRadius = 50.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Melee|Combo")
    float ComboResetDelay = 0.4f;

    int32 ComboIndex = 0;
    FTimerHandle ComboResetTimerHandle;
    void ResetCombo();

    UFUNCTION()
    void CanAttackTagEventReceived(FGameplayEventData EventData);

    UFUNCTION()
    void AttackTraceEventReceived(FGameplayEventData EventData);

    void TraceTakeResults(const TArray<FHitResult>& HitResults) const;
};