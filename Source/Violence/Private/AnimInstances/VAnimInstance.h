// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "VAnimInstance.generated.h"

class AVCharacter;
class UCharacterMovementComponent;

UCLASS()
class UVAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

    UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
    FORCEINLINE float GetWalkingSpeed() const { return WalkingSpeed; }

    UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
    FORCEINLINE bool GetHasAcceleration() const { return bHasAcceleration; }

    UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
    FORCEINLINE float GetLeanAngle() const { return LeanAngle; }

    UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
    FORCEINLINE float GetSlopeAngle() const { return SlopeAngle; }

    UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
    FORCEINLINE bool GetIsJumping() const { return bIsJumping; }

    UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
    FORCEINLINE bool GetIsMovingOnGround() const { return !bIsJumping; }

    UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
    FORCEINLINE float GetAimRotationOffsetPitch() const { return AimRotationOffset.Pitch; }

    UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
    FORCEINLINE float GetAimRotationOffsetYaw() const { return AimRotationOffset.Yaw; }

    UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
    bool ShouldPlayUpperBody() const;
    
private:
    UPROPERTY()
    AVCharacter* OwnerVCharacter;

    UPROPERTY()
    UCharacterMovementComponent* OwnerCharacterMovement;
    
    float WalkingSpeed;
    bool bHasAcceleration;

    UPROPERTY(EditDefaultsOnly, Category = "View")
    float LeanAngleInterpSpeed = 1.0f;

    UPROPERTY(EditDefaultsOnly, Category = "View")
    float SlopeAngleInterpSpeed = 1.0f;

    float LeanAngle;
    float SlopeAngle;
    FRotator LastRotation;
    FRotator LastAimRotation;
    FRotator AimRotationOffset;

    bool bIsJumping = false;
};