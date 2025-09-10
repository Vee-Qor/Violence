// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "VCharacter.generated.h"

class UVAbilitySystemComponent;
class UVAttributeSet;
class UVDefaultAbilitySet;

UCLASS()
class AVCharacter : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    AVCharacter();
    virtual void OnRep_PlayerState() override;
    void ServerInitial();
    void ClientInitial();

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    virtual UVAbilitySystemComponent* GetVAbilitySystemComponent() const;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleDefaultsOnly, Category = "AbilitySystem")
    UVAbilitySystemComponent* VAbilitySystemComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = "AbilitySystem")
    UVAttributeSet* VAttributeSet;

    UPROPERTY(EditDefaultsOnly, Category = "Abilities")
    UVDefaultAbilitySet* DefaultAbilitySet;
};