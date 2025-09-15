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
    TSubclassOf<UGameplayEffect> DamageEffect;

    UPROPERTY(EditDefaultsOnly, Category = "Primary Attack")
    float TraceSphereRadius = 50.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Primary Attack")
    float ComboResetDelay = 0.5f;

    int32 CurrentComboIndex = 0;
    FTimerHandle ComboResetTimerHandle;
    void ResetCombo();

    UFUNCTION()
    void TraceEventReceived(FGameplayEventData EventData);
    
    void TraceTakeResults(const TArray<FHitResult>& HitResults) const;
};