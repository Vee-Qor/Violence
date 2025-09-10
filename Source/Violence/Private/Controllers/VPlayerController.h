// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VPlayerController.generated.h"

UCLASS()
class AVPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void OnPossess(APawn* InPawn) override;
    virtual void AcknowledgePossession(class APawn* InPawn) override;

};