// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/VGameplayAbility.h"
#include "VGA_HitReact.generated.h"

UENUM()
enum class EVHitReactSides :uint8
{
    Front,
    Back,
    Right,
    Left
};

UCLASS()
class UVGA_HitReact : public UVGameplayAbility
{
    GENERATED_BODY()

public:
    UVGA_HitReact();
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "HitReact|Animation")
    TMap<EVHitReactSides, UAnimMontage*> HitReactMap;

    UPROPERTY(Transient)
    UAnimMontage* SelectedHitReactMontage;

    void SelectHitReactMontage(const FGameplayEventData* TriggerEventData);
};