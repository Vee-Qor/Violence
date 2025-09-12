// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AnimInstances/VAnimInstance.h"

#include "Characters/VCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UVAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    OwnerVCharacter = Cast<AVCharacter>(TryGetPawnOwner());
    if (OwnerVCharacter)
    {
        OwnerCharacterMovement = OwnerVCharacter->GetCharacterMovement();
        LastRotation = OwnerVCharacter->GetActorRotation();
        LastAimRotation = OwnerVCharacter->GetBaseAimRotation();
    }
}

void UVAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (!OwnerVCharacter || !OwnerCharacterMovement) return;

    WalkingSpeed = OwnerVCharacter->GetVelocity().Size2D();

    bHasAcceleration = OwnerCharacterMovement->GetCurrentAcceleration().SizeSquared2D() > 0.0f;

    FRotator CurrentRotation = OwnerVCharacter->GetActorRotation();
    FRotator DeltaRotation = UKismetMathLibrary::NormalizedDeltaRotator(CurrentRotation, LastRotation);
    LastRotation = CurrentRotation;
    LeanAngle = UKismetMathLibrary::FInterpTo(LeanAngle, DeltaRotation.Yaw / DeltaSeconds, DeltaSeconds, LeanAngleInterpSpeed);

    FRotator CurrentAimRotation = OwnerVCharacter->GetBaseAimRotation();
    AimRotationOffset = UKismetMathLibrary::NormalizedDeltaRotator(CurrentAimRotation, CurrentRotation);

    FRotator DeltaAimRotation = UKismetMathLibrary::NormalizedDeltaRotator(CurrentAimRotation, LastAimRotation);
    LastAimRotation = CurrentAimRotation;
    SlopeAngle = UKismetMathLibrary::FInterpTo(SlopeAngle, DeltaAimRotation.Pitch / DeltaSeconds, DeltaSeconds, SlopeAngleInterpSpeed);

    bIsJumping = OwnerCharacterMovement->IsFalling() && !OwnerCharacterMovement->IsMovingOnGround();
}

bool UVAnimInstance::ShouldPlayUpperBody() const
{
    if (GetHasAcceleration() || GetIsJumping())
    {
        return true;
    }

    return false;
}