// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "VBTService_UpdateFocus.generated.h"

UCLASS()
class UVBTService_UpdateFocus : public UBTService
{
    GENERATED_BODY()

public:
    UVBTService_UpdateFocus();
    virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
    UPROPERTY(EditAnywhere, Category = "Target")
    FBlackboardKeySelector TargetActorKey;
};