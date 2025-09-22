// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AI/BTTasks/VBTTask_ActivateAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AIController.h"

EBTNodeResult::Type UVBTTask_ActivateAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) return EBTNodeResult::Failed;

    APawn* Pawn = AIController->GetPawn();
    if (!Pawn) return EBTNodeResult::Failed;

    UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Pawn);
    if (!ASC || !AbilityToActivate) return EBTNodeResult::Failed;

    if (ASC->TryActivateAbilityByClass(AbilityToActivate))
    {
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}