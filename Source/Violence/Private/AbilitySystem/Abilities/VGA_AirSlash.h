// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/VGameplayAbility.h"
#include "VGA_AirSlash.generated.h"

UCLASS()
class UVGA_AirSlash : public UVGameplayAbility
{
    GENERATED_BODY()

public:
    UVGA_AirSlash();
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
        bool bReplicateEndAbility, bool bWasCancelled) override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* AirSlashMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Primary Attack")
    float TraceSphereRadius = 50.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Primary Attack")
    TSubclassOf<UGameplayEffect> DamageEffect;

    UFUNCTION()
    void TraceEventReceived(FGameplayEventData EventData);

    void TraceTakeResults(const TArray<FHitResult>& HitResults) const;
};