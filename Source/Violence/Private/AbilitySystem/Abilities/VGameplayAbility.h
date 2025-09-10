// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "VGameplayAbility.generated.h"

class AVCharacter;

UCLASS()
class UVGameplayAbility : public UGameplayAbility
{
    GENERATED_BODY()

public:
    AVCharacter* GetVCharacterFromActorInfo() const;

};