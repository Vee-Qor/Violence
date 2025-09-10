// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "VDefaultAbilitySet.generated.h"

class UVAbilitySystemComponent;
class UGameplayEffect;

UCLASS()
class UVDefaultAbilitySet : public UDataAsset
{
    GENERATED_BODY()

public:
    TArray<TSubclassOf<UGameplayEffect>> GetGameplayEffects() const { return InitialEffects; }

private:
    UPROPERTY(EditDefaultsOnly, Category = "Effects")
    TArray<TSubclassOf<UGameplayEffect>> InitialEffects;
};