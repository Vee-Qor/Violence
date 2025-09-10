// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "Characters/VCharacter.h"

#include "AbilitySystem/VAbilitySystemComponent.h"
#include "AbilitySystem/VAttributeSet.h"
#include "DataAssets/VDefaultAbilitySet.h"

AVCharacter::AVCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    VAbilitySystemComponent = CreateDefaultSubobject<UVAbilitySystemComponent>("VAbility System Component");
    VAttributeSet = CreateDefaultSubobject<UVAttributeSet>("VAttribute Set");
}

void AVCharacter::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    VAbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AVCharacter::ServerInitial()
{
    VAbilitySystemComponent->InitAbilityActorInfo(this, this);
    VAbilitySystemComponent->ApplyInitialEffects(DefaultAbilitySet->GetGameplayEffects());
}

void AVCharacter::ClientInitial()
{
    VAbilitySystemComponent->InitAbilityActorInfo(this, this);
}

UAbilitySystemComponent* AVCharacter::GetAbilitySystemComponent() const
{
    return VAbilitySystemComponent;
}

void AVCharacter::BeginPlay()
{
    Super::BeginPlay();
}