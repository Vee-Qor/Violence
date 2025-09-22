// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "VBTService_UpdateDistToTarget.generated.h"

UCLASS()
class UVBTService_UpdateDistToTarget : public UBTService
{
    GENERATED_BODY()

public:
    UVBTService_UpdateDistToTarget();
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
    UPROPERTY(EditAnywhere, Category = "Target")
    FBlackboardKeySelector TargetActorKey;

    UPROPERTY(EditAnywhere, Category = "Target")
    FBlackboardKeySelector DistToTargetKey;

    void UpdateDistance(UBehaviorTreeComponent& OwnerComp) const;
};