// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "Characters/VBuffBlack.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AVBuffBlack::AVBuffBlack()
{
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = true;
    bUseControllerRotationRoll = false;

    GetCapsuleComponent()->SetCapsuleSize(70.0f, 80.0f);

    GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
    GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -80.0f));
    GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
    GetMesh()->SetRelativeScale3D(FVector(0.6f, 0.6f, 0.6f));

    GetCharacterMovement()->bUseControllerDesiredRotation = true;
    GetCharacterMovement()->bOrientRotationToMovement = false;
}