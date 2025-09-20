// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "Controllers/VAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Characters/VCharacter.h"

AVAIController::AVAIController()
{
    AISightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("AI Sight Config");
    AISightConfig->DetectionByAffiliation.bDetectEnemies = true;
    AISightConfig->DetectionByAffiliation.bDetectFriendlies = false;
    AISightConfig->DetectionByAffiliation.bDetectNeutrals = false;
    AISightConfig->SightRadius = 1500.0f;
    AISightConfig->LoseSightRadius = 2000.0f;
    AISightConfig->SetMaxAge(5.0f);
    AISightConfig->PeripheralVisionAngleDegrees = 90.0f;

    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AI Perception Component");
    AIPerceptionComponent->ConfigureSense(*AISightConfig);
    AIPerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());
    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AVAIController::TargetPerceptionUpdated);
}

void AVAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (AVCharacter* VCharacter = Cast<AVCharacter>(InPawn))
    {
        VCharacter->ServerInitial();
    }

    SetGenericTeamId(FGenericTeamId(3));

    check(BehaviorTree);
    RunBehaviorTree(BehaviorTree);
}

void AVAIController::TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
    if (!BlackboardComponent) return;
    BlackboardComponent->SetValueAsObject(FName("Target"), Actor);
}