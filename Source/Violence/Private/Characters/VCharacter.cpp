// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "Characters/VCharacter.h"

#include "AbilitySystem/VAbilitySystemComponent.h"
#include "AbilitySystem/VAttributeSet.h"
#include "DataAssets/VDefaultAbilitySet.h"
#include "GameFramework/CharacterMovementComponent.h"

AVCharacter::AVCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    AbilitySystemComponent = CreateDefaultSubobject<UVAbilitySystemComponent>("VAbility System Component");
    AttributeSet = CreateDefaultSubobject<UVAttributeSet>("VAttribute Set");

    
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UVAttributeSet::GetMovementSpeedAttribute()).AddUObject(this, &AVCharacter::MovementSpeedChanged);
}

void AVCharacter::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AVCharacter::ServerInitial()
{
    check(DefaultAbilitySet);

    AbilitySystemComponent->InitAbilityActorInfo(this, this);
    AbilitySystemComponent->ApplyInitialEffects(DefaultAbilitySet->GetInitialEffects());
    AbilitySystemComponent->GiveInitialAbilities(DefaultAbilitySet->GetInitialAbilities());
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

void AVCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AVCharacter::MovementSpeedChanged(const FOnAttributeChangeData& ChangeData)
{
   if (GetCharacterMovement())
   {
       GetCharacterMovement()->MaxWalkSpeed = ChangeData.NewValue;
   }
}