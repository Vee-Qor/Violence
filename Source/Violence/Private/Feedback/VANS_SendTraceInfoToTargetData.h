// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayTagContainer.h"
#include "VANS_SendTraceInfoToTargetData.generated.h"

UENUM(BlueprintType)
enum class EWeaponHand : uint8
{
    Right,
    Left,
    Both
};

UCLASS()
class UVANS_SendTraceInfoToTargetData : public UAnimNotifyState
{
    GENERATED_BODY()

public:
    virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
        const FAnimNotifyEventReference& EventReference) override;

private:
    UPROPERTY(EditAnywhere, Category = "Trace")
    FGameplayTag EventTag;

    UPROPERTY(EditAnywhere, Category = "Trace")
    uint8 MaxTraces = 5;

    UPROPERTY(EditAnywhere, Category = "Trace")
    EWeaponHand WeaponHand;

    UPROPERTY(EditAnywhere, Category = "Trace", meta = (EditCondition = "WeaponHand == EWeaponHand::Right || WeaponHand == EWeaponHand::Both"))
    FName RightSocketName;

    UPROPERTY(EditAnywhere, Category = "Trace", meta = (EditCondition = "WeaponHand == EWeaponHand::Left || WeaponHand == EWeaponHand::Both"))
    FName LeftSocketName;
};