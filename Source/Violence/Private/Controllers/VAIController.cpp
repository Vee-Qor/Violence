// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "Controllers/VAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/VCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Navigation/CrowdFollowingComponent.h"

AVAIController::AVAIController(const FObjectInitializer& ObjectInitializer) : Super(
    ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
    AISightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("AISightConfig");
    AISightConfig->DetectionByAffiliation.bDetectEnemies = true;
    AISightConfig->DetectionByAffiliation.bDetectFriendlies = false;
    AISightConfig->DetectionByAffiliation.bDetectNeutrals = false;
    AISightConfig->SightRadius = 1000.0f;
    AISightConfig->LoseSightRadius = 1200.0f;
    AISightConfig->SetMaxAge(5.0f);
    AISightConfig->PeripheralVisionAngleDegrees = 90.0f;

    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComponent");
    AIPerceptionComponent->ConfigureSense(*AISightConfig);
    AIPerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());
    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AVAIController::TargetPerceptionUpdated);
}

void AVAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    SetGenericTeamId(FGenericTeamId(3));

    if (AVCharacter* VCharacter = Cast<AVCharacter>(InPawn))
    {
        VCharacter->ServerInitial();
    }

    checkf(BehaviorTree, TEXT("Forgot assign BehaviorTree in %s"), *GetName());
    RunBehaviorTree(BehaviorTree);

    InitCrowdSettings();
}

void AVAIController::SetAllSenseEnabled(bool bEnable) const
{
    if (!AIPerceptionComponent) return;
    AIPerceptionComponent->SetSenseEnabled(UAISense_Sight::StaticClass(), bEnable);
}

void AVAIController::TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
    if (!BlackboardComponent) return;
    BlackboardComponent->SetValueAsObject(FName("Target"), Actor);
}

void AVAIController::InitCrowdSettings() const
{
    if (UCrowdFollowingComponent* CrowdComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
    {
        CrowdComponent->SetCrowdSimulationState(bEnableCrowdSimulation ? ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled);

        switch (CrowdAvoidanceQuality)
        {
            case 1: CrowdComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);
                break;
            case 2: CrowdComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);
                break;
            case 3: CrowdComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);
                break;
            case 4: CrowdComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
                break;
        }

        CrowdComponent->SetAvoidanceGroup(1);
        CrowdComponent->SetGroupsToAvoid(1);

        CrowdComponent->SetCrowdSeparation(true);
        CrowdComponent->SetCrowdSeparationWeight(CrowdSeparationWeight);

        CrowdComponent->SetCrowdAnticipateTurns(true);
        CrowdComponent->SetCrowdObstacleAvoidance(true);

        CrowdComponent->SetCrowdPathOffset(true);
        CrowdComponent->SetCrowdCollisionQueryRange(CrowdCollisionQueryRange);
        CrowdComponent->SetCrowdPathOptimizationRange(CrowdPathOptimizationRange);
    }
}