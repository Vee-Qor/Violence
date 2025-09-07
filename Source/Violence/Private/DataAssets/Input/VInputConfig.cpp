// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "DataAssets/Input/VInputConfig.h"

const UInputAction* UVInputConfig::FindInputActionByTag(const FGameplayTag& InputTag) const
{
    if (NativeInputActions.Num() == 0)
    {
        return nullptr;
    }

    for (const FVInputActionMapping& Config : NativeInputActions)
    {
        if (Config.InputTag == InputTag && Config.InputAction)
        {
            return Config.InputAction;
        }
    }

    return nullptr;
}