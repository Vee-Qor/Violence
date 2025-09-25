// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "VCharacter.generated.h"

class UVAbilitySystemComponent;
class UVAttributeSet;
class UVDefaultAbilitySet;
struct FOnAttributeChangeData;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTraceTakeHitResultsSignature, const TArray<FHitResult>& /*HitResults*/);

UCLASS()
class AVCharacter : public ACharacter, public IAbilitySystemInterface, public IGenericTeamAgentInterface
{
    GENERATED_BODY()

public:
    AVCharacter();
    FOnTraceTakeHitResultsSignature OnTraceTakeHitResults;
    virtual void OnRep_PlayerState() override;
    void ServerInitial();
    void ClientInitial();

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    virtual UVAbilitySystemComponent* GetVAbilitySystemComponent() const;
    virtual FGenericTeamId GetGenericTeamId() const override;

    void SetRagdollState(const bool bNewState);
    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleDefaultsOnly, Category = "AbilitySystem")
    UVAbilitySystemComponent* AbilitySystemComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = "AbilitySystem")
    UVAttributeSet* AttributeSet;

    UPROPERTY(EditDefaultsOnly, Category = "Abilities")
    UVDefaultAbilitySet* CharacterAbilitySet;

    void MovementSpeedChanged(const FOnAttributeChangeData& ChangeData);
    void HealthChanged(const FOnAttributeChangeData& ChangeData);
    
    UPROPERTY(ReplicatedUsing = OnRep_IsRagdoll)
    bool bIsRagdoll;

    UFUNCTION()
    void OnRep_IsRagdoll();
};