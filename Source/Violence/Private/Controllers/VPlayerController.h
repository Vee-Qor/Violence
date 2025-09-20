// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "VPlayerController.generated.h"

UCLASS()
class AVPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
    GENERATED_BODY()

public:
    virtual void OnPossess(APawn* InPawn) override;
    virtual void AcknowledgePossession(class APawn* InPawn) override;

    virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override { TeamID = NewTeamID; }
    virtual FGenericTeamId GetGenericTeamId() const override { return TeamID; }

private:
    FGenericTeamId TeamID;
};