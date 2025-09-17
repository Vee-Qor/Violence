// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AbilitySystem/Abilities/VGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Characters/VCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

AVCharacter* UVGameplayAbility::GetVCharacterFromActorInfo() const
{
    if (CurrentActorInfo && CurrentActorInfo->AvatarActor.IsValid())
    {
        return Cast<AVCharacter>(CurrentActorInfo->AvatarActor.Get());
    }

    return nullptr;
}

void UVGameplayAbility::StartTraceTimer(const FGameplayEventData& EventData, const float SphereRadius)
{
    HitActors.Empty();
    PrevSocketLocations.Empty();

    uint8 MaxTraces = 0;
    TraceStepIndex = 0;

    USkeletalMeshComponent* SkeletalMeshComponent = GetOwningComponentFromActorInfo();
    if (!SkeletalMeshComponent) return;

    for (const TSharedPtr<FGameplayAbilityTargetData>& TargetData : EventData.TargetData.Data)
    {
        if (TargetData.IsValid() && TargetData->GetHitResult() && !TargetData->GetHitResult()->MyBoneName.IsNone())
        {
            FName SocketName = TargetData->GetHitResult()->MyBoneName;
            FVector SocketLocation = SkeletalMeshComponent->GetSocketLocation(SocketName);

            PrevSocketLocations.Add(SocketName, SocketLocation);
        }

        if (TargetData->GetHitResult()->ElementIndex)
        {
            MaxTraces = TargetData->GetHitResult()->ElementIndex;
        }
    }

    if (MaxTraces <= 0) return;

    const float TotalDuration = EventData.EventMagnitude;
    const float TraceInterval = TotalDuration / MaxTraces;
    const float TraceFirstDelay = TraceInterval;

    if (GetWorld())
    {
        const FTimerDelegate TimerDel = FTimerDelegate::CreateUObject(this, &UVGameplayAbility::PerformTraceStep, SphereRadius, MaxTraces);
        GetWorld()->GetTimerManager().SetTimer(SwordTimerHandle, TimerDel, TraceInterval, true, TraceFirstDelay);
    }
}

void UVGameplayAbility::ApplyDamageFromHitResults(const TArray<FHitResult>& HitResults, const TSubclassOf<UGameplayEffect>& DamageEffect) const
{
    for (const FHitResult& HitResult : HitResults)
    {
        UE_LOG(LogTemp, Warning, TEXT("HitActor: %s"), *HitResult.GetActor()->GetName());

        FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffect, GetAbilityLevel(CurrentSpecHandle, CurrentActorInfo));

        FGameplayEffectContextHandle EffectContextHandle = MakeEffectContext(CurrentSpecHandle, CurrentActorInfo);
        EffectContextHandle.AddHitResult(HitResult);
        EffectSpecHandle.Data->SetContext(EffectContextHandle);

        ApplyGameplayEffectSpecToTarget(GetCurrentAbilitySpecHandle(), CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle,
            UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(HitResult.GetActor()));
    }
}

void UVGameplayAbility::PerformTraceStep(const float SphereRadius, const uint8 MaxTraces)
{
    if (TraceStepIndex >= MaxTraces)
    {
        GetWorld()->GetTimerManager().ClearTimer(SwordTimerHandle);
        PrevSocketLocations.Empty();
        return;
    }

    USkeletalMeshComponent* SkeletalMeshComponent = GetOwningComponentFromActorInfo();
    if (!SkeletalMeshComponent) return;

    TArray<FHitResult> HitResults;

    for (auto& Elem : PrevSocketLocations)
    {
        FName SocketName = Elem.Key;
        FVector PrevLocation = Elem.Value;
        FVector CurrentLocation = SkeletalMeshComponent->GetSocketLocation(SocketName);

        TArray<FHitResult> StepResults = DoTraceAndGetUniqueActors(PrevLocation, CurrentLocation, SphereRadius, HitActors);
        HitResults.Append(StepResults);

        Elem.Value = CurrentLocation;
    }

    TraceStepIndex++;
    OnTraceTakeHitResults.Broadcast(HitResults);
}

TArray<FHitResult> UVGameplayAbility::DoTraceAndGetUniqueActors(const FVector& TraceStart, const FVector& TraceEnd, const float TraceSphereRadius,
    TSet<AActor*>& OutHitActors) const
{
    TArray<FHitResult> OutResults;

    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

    TArray<AActor*> IgnoredActors;
    IgnoredActors.Add(GetAvatarActorFromActorInfo());

    EDrawDebugTrace::Type DrawDebug = bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;

    TArray<FHitResult> HitResults;

    UKismetSystemLibrary::SphereTraceMultiForObjects(this, TraceStart, TraceEnd, TraceSphereRadius, ObjectTypes, false, IgnoredActors, DrawDebug, HitResults, false);
    for (const FHitResult& HitResult : HitResults)
    {
        if (!HitResult.GetActor() || OutHitActors.Contains(HitResult.GetActor())) continue;

        OutHitActors.Add(HitResult.GetActor());
        OutResults.Add(HitResult);
    }

    return OutResults;
}