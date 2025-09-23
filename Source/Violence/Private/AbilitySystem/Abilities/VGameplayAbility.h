// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "VGameplayAbility.generated.h"

class AVCharacter;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTraceTakeHitResultsSignature, const TArray<FHitResult>& /*HitResults*/);

UCLASS()
class UVGameplayAbility : public UGameplayAbility
{
    GENERATED_BODY()

public:
    virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
    AVCharacter* GetVCharacterFromActorInfo() const;
    FORCEINLINE bool ShouldDrawDebug() const { return bDrawDebug; }
    FORCEINLINE float GetCachedAttackSpeed() const { return CachedAttackSpeed; }

private:
    UPROPERTY(EditDefaultsOnly, Category = "Debug")
    bool bDrawDebug = true;

    UPROPERTY()
    float CachedAttackSpeed;

    void AttackSpeedChanged(const FOnAttributeChangeData& ChangeData);

    /******* Sword Attack *******/
protected:
    FOnTraceTakeHitResultsSignature OnTraceTakeHitResults;
    void StartTraceTimer(const FGameplayEventData& EventData, const float SphereRadius);
    void ApplyDamageFromHitResults(const TArray<FHitResult>& HitResults, const TSubclassOf<UGameplayEffect>& DamageEffect) const;

    UFUNCTION()
    virtual void CanAttackTagEventReceived(FGameplayEventData EventData);

private:
    void PerformTraceStep(const float SphereRadius, const uint8 MaxTraces);
    TArray<FHitResult> DoTraceAndGetUniqueActors(const FVector& TraceStart, const FVector& TraceEnd, const float TraceSphereRadius,
        TSet<AActor*>& OutHitActors) const;

    UPROPERTY()
    TMap<FName, FVector> PrevSocketLocations;

    FTimerHandle SwordTimerHandle;
    int32 TraceStepIndex;

    UPROPERTY()
    TSet<AActor*> HitActors;
};