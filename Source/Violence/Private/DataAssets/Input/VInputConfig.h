// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "VInputConfig.generated.h"

class UInputAction;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FVInputActionMapping
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, meta = (Categories = "InputTag"))
    FGameplayTag InputTag;

    UPROPERTY(EditDefaultsOnly)
    UInputAction* InputAction = nullptr;

    bool IsValid() const { return InputTag.IsValid() && InputAction; }
};

UCLASS()
class UVInputConfig : public UDataAsset
{
    GENERATED_BODY()

public:
    const UInputAction* FindInputActionByTag(const FGameplayTag& InputTag) const;

    FORCEINLINE UInputMappingContext* GetDefaultInputMappingContext() const { return DefaultInputMappingContext; }
    FORCEINLINE const TArray<FVInputActionMapping>& GetAbilityInputActions() const { return AbilityInputActions; }

private:
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputMappingContext* DefaultInputMappingContext;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TArray<FVInputActionMapping> NativeInputActions;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TArray<FVInputActionMapping> AbilityInputActions;
};