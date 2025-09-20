// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AI/BTTasks/BTTask_ActivateAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_ActivateAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (OwnerComp.GetAIOwner())
    {
        APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
        if (!Pawn) return EBTNodeResult::Failed;

        UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Pawn);
        if (!ASC || !AbilityToActivate) return EBTNodeResult::Failed;

        if (ASC->TryActivateAbilityByClass(AbilityToActivate))
        {
            return EBTNodeResult::Succeeded;
        }
    }

    return EBTNodeResult::Failed;
}