// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/VGameplayAbility.h"
#include "VGA_Jump.generated.h"

UCLASS()
class UVGA_Jump : public UVGameplayAbility
{
    GENERATED_BODY()

public:
    UVGA_Jump();
    virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr,
        OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData) override;

private:
    UFUNCTION()
    void OnCharacterLanded(const FHitResult& Hit);

    UPROPERTY(EditDefaultsOnly, Category = "GameplayCue")
    FGameplayTag CameraShakeCueTag;
};