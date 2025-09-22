// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "VBTTask_ActivateAbility.generated.h"

class UGameplayAbility;

UCLASS()
class UVBTTask_ActivateAbility : public UBTTaskNode
{
    GENERATED_BODY()

public:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
    UPROPERTY(EditAnywhere, Category = "Ability")
    TSubclassOf<UGameplayAbility> AbilityToActivate;
};