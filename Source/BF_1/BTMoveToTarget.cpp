// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "BTMoveToTarget.h"
#include "AIPatrolPoint.h"
#include "AIPatrolController.h"
#include "BehaviorTree/BlackboardComponent.h"



EBTNodeResult::Type UBTMoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwerComp, uint8* NodeMemory)
{

	AAIPatrolController* AICon = Cast<AAIPatrolController>(OwerComp.GetAIOwner());

	if (AICon)
	{
		TArray<AActor*> AvailablePatrolPoints = AICon->GetPatrolPoints();

		AActor* NextPatrolPoint = AvailablePatrolPoints[AICon->CurrentPatrolPoint];

		

		//if (AICon->GetCurrentMoveRequestID().IsValid)//IsEquivalent;//MoveToActor.GetCurrentMoveRequestID();
		//if (AICon->GetMoveStatus()); //AICon->GetMoveGoalReachTest(AICon, , NextPatrolPoint, 5.f, 5.f
		
		//if(AICon->GetPawn()->GetDistanceTo(NextPatrolPoint) < 10.1f)
		if (AICon->GetMoveStatus() == EPathFollowingStatus::Idle)
		{
			//EPathFollowingStatus::Moving;
			//AICon->GetMoveGoalOffset(AICon);
			AICon->MoveToActor(NextPatrolPoint, 5.f, true, true, true, 0, true);
			return EBTNodeResult::Succeeded;
		}
		else {
			//return EBTNodeResult::InProgress;
		}

		

		
		//AICon->ReceiveMoveCompleted;
	}


	//just in case
	return EBTNodeResult::Failed;

}