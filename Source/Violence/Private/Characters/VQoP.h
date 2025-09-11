// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/VCharacter.h"
#include "GameplayTagContainer.h"
#include "VQoP.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UVInputConfig;
struct FInputActionValue;

UCLASS()
class AVQoP : public AVCharacter
{
    GENERATED_BODY()

public:
    AVQoP();
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