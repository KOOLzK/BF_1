// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTService.h"
#include "BTService_CheckLights.generated.h"

/**
*
*/
UCLASS()
class BF_1_API UBTService_CheckLights : public UBTService
{
	GENERATED_BODY()

	UBTService_CheckLights();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;



};
