// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/VGameplayAbility.h"
#include "VGA_Respawn.generated.h"

UCLASS()
class UVGA_Respawn : public UVGameplayAbility
{
    GENERATED_BODY()

public:
    UVGA_Respawn();
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Respawn|Animation")
    UAnimMontage* RespawnMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Respawn|Effects")
    TSubclassOf<UGameplayEffect> RespawnEffect;

    UPROPERTY(EditDefaultsOnly, Category = "Respawn|Effects")
    TSubclassOf<UGameplayEffect> DeadEffectToRemove;

    UPROPERTY(EditDefaultsOnly, Category = "Death|VFX", meta = (Categories = "GameplayCue"))
    FGameplayTag RespawnDissolveCueTag;

    UPROPERTY(EditDefaultsOnly, Category = "Death|VFX")
    float DissolveDuration = 1.0f;

    void ApplyRespawnState();

    UFUNCTION()
    void EnableInput();
};