// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AI/BTServices/VBTService_UpdateDistToTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UVBTService_UpdateDistToTarget::UVBTService_UpdateDistToTarget()
{
    NodeName = "Update Distance To Target";

    bCallTickOnSearchStart = true;

    TargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UVBTService_UpdateDistToTarget, TargetActorKey), AActor::StaticClass());
    DistToTargetKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UVBTService_UpdateDistToTarget, DistToTargetKey));
}

void UVBTService_UpdateDistToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    UpdateDistance(OwnerComp);
}

void UVBTService_UpdateDistToTarget::UpdateDistance(UBehaviorTreeComponent& OwnerComp) const
{
    const AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) return;

    const APawn* Pawn = AIController->GetPawn();
    if (!Pawn) return;

    UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComponent) return;

    const AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(TargetActorKey.SelectedKeyName));
    if (!TargetActor) return;

    const float DistanceToTarget = Pawn->GetDistanceTo(TargetActor);

    BlackboardComponent->SetValueAsFloat(DistToTargetKey.SelectedKeyName, DistanceToTarget);
}