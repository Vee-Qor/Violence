// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "VAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class AVAIController : public AAIController
{
    GENERATED_BODY()

public:
    AVAIController(const FObjectInitializer& ObjectInitializer);
    virtual void OnPossess(APawn* InPawn) override;
    void SetAllSenseEnabled(bool bEnable) const;

private:
    UPROPERTY(EditDefaultsOnly, Category = "AI")
    UBehaviorTree* BehaviorTree;

    UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
    UAIPerceptionComponent* AIPerceptionComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
    UAISenseConfig_Sight* AISightConfig;

    UFUNCTION()
    void TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

    void InitCrowdSettings() const;

    UPROPERTY(EditDefaultsOnly, Category = "Crowd")
    bool bEnableCrowdSimulation = true;

    UPROPERTY(EditDefaultsOnly, Category = "Crowd", meta=(ClampMin = "0", ClampMax = "4", EditCondition = "bEnableCrowdSimulation"))
    int32 CrowdAvoidanceQuality = 4;

    UPROPERTY(EditDefaultsOnly, Category = "Crowd", meta=(EditCondition="bEnableCrowdSimulation"))
    float CrowdCollisionQueryRange = 600.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Crowd", meta=(EditCondition = "bEnableCrowdSimulation"))
    float CrowdPathOptimizationRange = 1000.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Crowd", meta=(EditCondition = "bEnableCrowdSimulation"))
    float CrowdSeparationWeight = 2.0f;
};