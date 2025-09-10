// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/VCharacter.h"
#include "GameplayTagContainer.h"
#include "VQueenOfPain.generated.h"

class UVInputConfig;
class UCameraComponent;
class USpringArmComponent;
struct FInputActionValue;

UCLASS()
class AVQueenOfPain : public AVCharacter
{
    GENERATED_BODY()

public:
    AVQueenOfPain();
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void PawnClientRestart() override;

private:
    UPROPERTY(VisibleDefaultsOnly, Category = "Camera")
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleDefaultsOnly, Category = "Camera")
    UCameraComponent* FollowCamera;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UVInputConfig* InputConfig;

    void HandleMoveInput(const FInputActionValue& InputActionValue);
    void HandleLookInput(const FInputActionValue& InputActionValue);
    void HandleAbilityInputPressed(const FGameplayTag InputTag);
    void HandleAbilityInputReleased(const FGameplayTag InputTag);
};