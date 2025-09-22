// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AI/EQS/VEQC_Target.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void UVEQC_Target::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
    Super::ProvideContext(QueryInstance, ContextData);

    AActor* Actor = Cast<AActor>(QueryInstance.Owner.Get());
    if (!Actor) return;

    const UBlackboardComponent* BlackboardComponent = UAIBlueprintHelperLibrary::GetBlackboard(Actor);
    if (!BlackboardComponent) return;

    const AActor* ContextActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(TargetKeyName));
    UEnvQueryItemType_Actor::SetContextHelper(ContextData, ContextActor);
}