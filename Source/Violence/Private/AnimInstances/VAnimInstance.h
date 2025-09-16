// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "VAnimInstance.generated.h"

class AVCharacter;
class UCharacterMovementComponent;
struct FGameplayTag;


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
    
    UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
    bool GetIsInCombat() const { return bIsInCombat; }

    UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
    bool GetIsInTravel() const { return bIsInCombat; }

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
    bool bIsInCombat = false;
    bool bIsInTravel = false;

    void CombatTagChanged(const FGameplayTag Tag, int32 NewCount);
    void TravelTagChanged(const FGameplayTag Tag, int32 NewCount);
};