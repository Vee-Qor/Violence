// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "Controllers/VPlayerController.h"

#include "Characters/VCharacter.h"

void AVPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (AVCharacter* VCharacter = Cast<AVCharacter>(InPawn))
    {
        VCharacter->ServerInitial();
    }

    SetGenericTeamId(FGenericTeamId(2));
}

void AVPlayerController::AcknowledgePossession(class APawn* InPawn)
{
    Super::AcknowledgePossession(InPawn);

    if (AVCharacter* VCharacter = Cast<AVCharacter>(InPawn))
    {
        VCharacter->ClientInitial();
    }
}