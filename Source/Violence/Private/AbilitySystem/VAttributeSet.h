// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "VAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class UVAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    ATTRIBUTE_ACCESSORS(UVAttributeSet, Health);
    ATTRIBUTE_ACCESSORS(UVAttributeSet, MaxHealth);

    ATTRIBUTE_ACCESSORS(UVAttributeSet, Resource);
    ATTRIBUTE_ACCESSORS(UVAttributeSet, MaxResource);

    ATTRIBUTE_ACCESSORS(UVAttributeSet, AttackSpeed);

    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

private:
    UPROPERTY(ReplicatedUsing = OnRep_Health)
    FGameplayAttributeData Health;

    UPROPERTY(ReplicatedUsing = OnRep_MaxHealth)
    FGameplayAttributeData MaxHealth;

    UPROPERTY(ReplicatedUsing = OnRep_Resource)
    FGameplayAttributeData Resource;

    UPROPERTY(ReplicatedUsing = OnRep_MaxResource)
    FGameplayAttributeData MaxResource;

    UPROPERTY(ReplicatedUsing = OnRep_AttackSpeed)
    FGameplayAttributeData AttackSpeed;

    UFUNCTION()
    void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

    UFUNCTION()
    void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

    UFUNCTION()
    void OnRep_Resource(const FGameplayAttributeData& OldResource) const;

    UFUNCTION()
    void OnRep_MaxResource(const FGameplayAttributeData& OldMaxResource) const;

    UFUNCTION()
    void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const;
};