// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "Characters/VCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/VAbilitySystemComponent.h"
#include "AbilitySystem/VAttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "DataAssets/AbilitySets/VDefaultAbilitySet.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "VGameplayTags.h"
#include "Net/UnrealNetwork.h"

AVCharacter::AVCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    AbilitySystemComponent = CreateDefaultSubobject<UVAbilitySystemComponent>("VAbility System Component");
    AttributeSet = CreateDefaultSubobject<UVAttributeSet>("VAttribute Set");

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UVAttributeSet::GetMovementSpeedAttribute()).AddUObject(this,
        &AVCharacter::MovementSpeedChanged);
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UVAttributeSet::GetHealthAttribute()).AddUObject(this,
        &AVCharacter::HealthChanged);
}

void AVCharacter::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AVCharacter::ServerInitial()
{
    check(CharacterAbilitySet);

    AbilitySystemComponent->InitAbilityActorInfo(this, this);
    CharacterAbilitySet->ApplyToASC(AbilitySystemComponent);
}

void AVCharacter::ClientInitial()
{
    AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

UAbilitySystemComponent* AVCharacter::GetAbilitySystemComponent() const
{
    return GetVAbilitySystemComponent();
}

UVAbilitySystemComponent* AVCharacter::GetVAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

FGenericTeamId AVCharacter::GetGenericTeamId() const
{
    if (const AController* CharacterController = GetController())
    {
        if (const IGenericTeamAgentInterface* ControllerTeamInterface = Cast<IGenericTeamAgentInterface>(CharacterController))
        {
            return ControllerTeamInterface->GetGenericTeamId();
        }
    }

    return FGenericTeamId::NoTeam;
}

void AVCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AVCharacter::MovementSpeedChanged(const FOnAttributeChangeData& ChangeData)
{
    UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
    if (!CharacterMovementComponent) return;

    CharacterMovementComponent->MaxWalkSpeed = ChangeData.NewValue;
}

void AVCharacter::HealthChanged(const FOnAttributeChangeData& ChangeData)
{
    if (!HasAuthority()) return;

    if (ChangeData.NewValue <= 0.0f)
    {
        UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, VGameplayTags::Common_Event_Death, FGameplayEventData{});
    }

    if (ChangeData.NewValue > 0.0f && ChangeData.GEModData)
    {
        const FGameplayEffectContextHandle& EffectContextHandle = ChangeData.GEModData->EffectSpec.GetEffectContext();
        if (!EffectContextHandle.IsValid() || EffectContextHandle.GetInstigator() == this) return;

        FGameplayEventData EventData;
        EventData.ContextHandle = EffectContextHandle;
        UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, VGameplayTags::Common_Event_Hit_React, EventData);
    }
}

void AVCharacter::SetRagdollState(const bool bNewState)
{
    if (!HasAuthority()) return;

    bIsRagdoll = bNewState;
    OnRep_IsRagdoll();
}

void AVCharacter::OnRep_IsRagdoll()
{
    UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
    USkeletalMeshComponent* SkeletalMesh = GetMesh();
    if (!SkeletalMesh || !CapsuleComp) return;

    CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SkeletalMesh->SetCollisionEnabled(bIsRagdoll ? ECollisionEnabled::PhysicsOnly : ECollisionEnabled::NoCollision);
    SkeletalMesh->SetSimulatePhysics(bIsRagdoll);
    SkeletalMesh->bPauseAnims = true;
    SkeletalMesh->bWaitForParallelClothTask = true;
}

void AVCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AVCharacter, bIsRagdoll);
}