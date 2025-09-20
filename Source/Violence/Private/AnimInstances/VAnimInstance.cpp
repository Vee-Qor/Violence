// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AnimInstances/VAnimInstance.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Characters/VCharacter.h"
#include "GameplayTagContainer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "VGameplayTags.h"
#include "KismetAnimationLibrary.h"
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

        UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerVCharacter);
        if (!ASC) return;

        ASC->RegisterGameplayTagEvent(VGameplayTags::Player_Status_Combat).AddUObject(this, &UVAnimInstance::CombatTagChanged);
        ASC->RegisterGameplayTagEvent(VGameplayTags::Player_Status_Travel).AddUObject(this, &UVAnimInstance::TravelTagChanged);
    }
}

void UVAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (!OwnerVCharacter || !OwnerCharacterMovement) return;

    WalkingSpeed = OwnerVCharacter->GetVelocity().Size2D();

    MovementDirection = UKismetAnimationLibrary::CalculateDirection(OwnerVCharacter->GetVelocity(), OwnerVCharacter->GetActorRotation());

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

void UVAnimInstance::CombatTagChanged(const FGameplayTag Tag, int32 NewCount)
{
    bIsInCombat = NewCount != 0;
}

void UVAnimInstance::TravelTagChanged(const FGameplayTag Tag, int32 NewCount)
{
    bIsInTravel = NewCount != 0;
}