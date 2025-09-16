// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"
#include "VAN_SendGameplayEvent.generated.h"

UCLASS()
class UVAN_SendGameplayEvent : public UAnimNotify
{
    GENERATED_BODY()

public:
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
    UPROPERTY(EditAnywhere, Category = "EventTag")
    FGameplayTag EventTag;
};