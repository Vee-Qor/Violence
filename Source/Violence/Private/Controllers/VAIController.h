// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "VAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class AVAIController : public AAIController
{
    GENERATED_BODY()

public:
    AVAIController();
    virtual void OnPossess(APawn* InPawn) override;

private:
    UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
    UAIPerceptionComponent* AIPerceptionComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
    UAISenseConfig_Sight* AISightConfig;

    UPROPERTY(EditDefaultsOnly, Category = "AI")
    UBehaviorTree* BehaviorTree;

    UFUNCTION()
    void TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};