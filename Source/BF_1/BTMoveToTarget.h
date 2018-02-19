// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTMoveToTarget.generated.h"

/**
 * 
 */
UCLASS()
class BF_1_API UBTMoveToTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwerComp, uint8* NodeMemory) override;
	
	//virtual void OnMoveCompleted(FAIRequestID RequestID, const EPathFollowingResult & Result) override;

	//virtual void OnPathFinished(EPathFollowingResult::Type Result) override;

	FVector Playerforward;
	FVector SearchLocation;
	FRotator RotationStart;

	bool BackFromSearch;
	bool SpinDone;
	bool StartNotSet;

	/*Ray Trace*/
	FHitResult* HitResult;
	FVector StartTrace;
	FVector ForwardVector;
	FVector EndTrace;
	FCollisionQueryParams* TraceParams;
};
