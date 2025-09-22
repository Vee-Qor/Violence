// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "VEQC_Target.generated.h"

UCLASS()
class UVEQC_Target : public UEnvQueryContext
{
    GENERATED_BODY()

public:
    virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

private:
    UPROPERTY(EditAnywhere)
    FName TargetKeyName = "Target";
};