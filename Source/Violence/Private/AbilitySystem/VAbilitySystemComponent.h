// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "VAbilitySystemComponent.generated.h"

UCLASS()
class UVAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
    void ApplyInitialEffects(const TArray<TSubclassOf<UGameplayEffect>>& GameplayEffects);
	
};
