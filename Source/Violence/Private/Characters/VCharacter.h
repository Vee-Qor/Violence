// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VCharacter.generated.h"

UCLASS()
class AVCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AVCharacter();

protected:
    virtual void BeginPlay() override;

};