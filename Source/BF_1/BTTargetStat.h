// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTargetStat.generated.h"

/**
 * should be BBTargetState i know
 */
UCLASS()
class BF_1_API UBTTargetStat : public UBTTaskNode
{
	GENERATED_BODY()
		/*Patrol moving between patrol points. 
		Spotted the enemy sees the player. 
		LastSeen enemy moves to the place the player was last seen. 
		Searching enemy has gone to the place where the player was last seen and didn't find the player. */
		enum State {patrol, spotted, lastSeen, searching};
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwerComp, uint8* NodeMemory) override;

};
