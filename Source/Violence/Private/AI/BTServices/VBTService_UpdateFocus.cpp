// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AI/BTServices/VBTService_UpdateFocus.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UVBTService_UpdateFocus::UVBTService_UpdateFocus()
{
    NodeName = "Update Focus";

    bNotifyTick = false;
    bNotifyBecomeRelevant = true;
    bNotifyCeaseRelevant = true;

    TargetActorKey.AddObjectFilter(this, TargetActorKey.SelectedKeyName, AActor::StaticClass());
}

void UVBTService_UpdateFocus::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::OnBecomeRelevant(OwnerComp, NodeMemory);

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) return;

    const UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComponent) return;

    AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(TargetActorKey.SelectedKeyName));
    if (!TargetActor) return;

    AIController->SetFocus(TargetActor);
}

void UVBTService_UpdateFocus::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::OnCeaseRelevant(OwnerComp, NodeMemory);

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) return;

    AIController->ClearFocus(EAIFocusPriority::Gameplay);
}