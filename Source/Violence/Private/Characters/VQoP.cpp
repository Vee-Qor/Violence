// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "Characters/VQoP.h"

#include "AbilitySystem/VAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/Input/VInputComponent.h"
#include "DataAssets/Input/VInputConfig.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "VGameplayTags.h"

AVQoP::AVQoP()
{
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    GetCapsuleComponent()->SetCapsuleSize(40.0f, 92.0f);

    GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
    GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -92.0f));
    GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);

    SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    SpringArm->SetupAttachment(GetRootComponent());
    SpringArm->bUsePawnControlRotation = true;
    SpringArm->bDoCollisionTest = true;
    SpringArm->TargetArmLength = 300.0f;
    SpringArm->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
    SpringArm->bEnableCameraLag = true;
    SpringArm->CameraLagSpeed = 5.0f;
    SpringArm->CameraLagMaxDistance = 100.0f;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>("Follow Camera");
    FollowCamera->SetupAttachment(SpringArm);
    FollowCamera->bUsePawnControlRotation = false;
}

void AVQoP::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Don't forgot change default input component.
    UVInputComponent* VInputComponent = CastChecked<UVInputComponent>(PlayerInputComponent);

    VInputComponent->BindNativeInputAction(InputConfig, VGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &AVQoP::HandleMoveInput);
    VInputComponent->BindNativeInputAction(InputConfig, VGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &AVQoP::HandleLookInput);

    VInputComponent->BindAbilityInputAction(InputConfig, this, &AVQoP::HandleAbilityInputPressed, &AVQoP::HandleAbilityInputReleased);
}

void AVQoP::PawnClientRestart()
{
    Super::PawnClientRestart();

    checkf(InputConfig, TEXT("Forgot to assign InputConfig in %s"), *GetName())
    ensureAlwaysMsgf(InputConfig->GetDefaultInputMappingContext(), TEXT("Input Mapping Context is empty in %s"), *InputConfig->GetName());

    const APlayerController* PlayerController = GetController<APlayerController>();
    if (!PlayerController) return;

    const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
    if (!LocalPlayer) return;

    UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    check(InputSubsystem);

    InputSubsystem->RemoveMappingContext(InputConfig->GetDefaultInputMappingContext());
    InputSubsystem->AddMappingContext(InputConfig->GetDefaultInputMappingContext(), 0);
}

void AVQoP::HandleMoveInput(const FInputActionValue& InputActionValue)
{
    const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
    const FRotator MovementRotator(0.0f, GetControlRotation().Yaw, 0.0f);

    if (MovementVector.Y != 0.0f)
    {
        const FVector ForwardDirection = MovementRotator.RotateVector(FVector::ForwardVector);

        AddMovementInput(ForwardDirection, MovementVector.Y);
    }

    if (MovementVector.X != 0.0f)
    {
        const FVector RightDirection = MovementRotator.RotateVector(FVector::RightVector);

        AddMovementInput(RightDirection, MovementVector.X);
    }
}

void AVQoP::HandleLookInput(const FInputActionValue& InputActionValue)
{
    const FVector2D LookVector = InputActionValue.Get<FVector2D>();

    if (LookVector.Y != 0.0f)
    {
        AddControllerPitchInput(LookVector.Y);
    }

    if (LookVector.X != 0.0f)
    {
        AddControllerYawInput(LookVector.X);
    }
}

void AVQoP::HandleAbilityInputPressed(const FGameplayTag InputTag)
{
    if (UVAbilitySystemComponent* OwnerVAbilitySystemComponent = GetVAbilitySystemComponent())
    {
        OwnerVAbilitySystemComponent->HandleAbilityInputPressed(InputTag);
    }
}

void AVQoP::HandleAbilityInputReleased(const FGameplayTag InputTag)
{
    if (UVAbilitySystemComponent* OwnerVAbilitySystemComponent = GetVAbilitySystemComponent())
    {
        OwnerVAbilitySystemComponent->HandleAbilityInputReleased(InputTag);
    }
}