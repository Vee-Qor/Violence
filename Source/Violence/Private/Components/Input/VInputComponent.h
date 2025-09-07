// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/VInputConfig.h"
#include "VInputComponent.generated.h"

UCLASS()
class UVInputComponent : public UEnhancedInputComponent
{
    GENERATED_BODY()

public:
    template <class UserObject, typename CallBack>
    void BindNativeInputAction(const UVInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserObject* Object, CallBack Func);

};

template <class UserObject, typename CallBack>
void UVInputComponent::BindNativeInputAction(const UVInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserObject* Object, CallBack Func)
{
    check(InputConfig);

    if (const UInputAction* FoundAction = InputConfig->FindInputActionByTag(InputTag))
    {
        BindAction(FoundAction, TriggerEvent, Object, Func);
    }
}