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

		//CurrentPatrolPoint changed in BTSelectPatrolPoint.cpp
		AActor* NextPatrolPoint = AvailablePatrolPoints[AICon->CurrentPatrolPoint];

		

		//if (AICon->GetCurrentMoveRequestID().IsValid)//IsEquivalent;//MoveToActor.GetCurrentMoveRequestID();
		//if (AICon->GetMoveStatus()); //AICon->GetMoveGoalReachTest(AICon, , NextPatrolPoint, 5.f, 5.f
		
		//if(AICon->GetPawn()->GetDistanceTo(NextPatrolPoint) < 10.1f)
		if (AICon->CurrentState == AAIPatrolController::State::patrol) {

			//when Idle it moves to the next Patrol Point and when it has completed the move it goes Idle
			if (AICon->GetMoveStatus() == EPathFollowingStatus::Idle)
			{
				//EPathFollowingStatus::Moving;
				//AICon->GetMoveGoalOffset(AICon);
				AICon->MoveToActor(NextPatrolPoint, 5.f, true, true, true, 0, true);
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::FromInt(AICon->CurrentPatrolPoint));
				return EBTNodeResult::Succeeded;
			}
			else {
				//return EBTNodeResult::InProgress;
			}
		}

		if (AICon->CurrentState == AAIPatrolController::State::spotted) {
			AICon->lastSeenTimer--;
			if (AICon->lastSeenTimer < 0) {
				AICon->CurrentState = AAIPatrolController::State::lastSeen;
			}
			AICon->MoveToLocation(AICon->LastLocation);
			return EBTNodeResult::Succeeded;
		}

		if (AICon->CurrentState == AAIPatrolController::State::lastSeen) {
			if (AICon->GetMoveStatus() == EPathFollowingStatus::Idle)
			{
				AICon->CurrentState = AAIPatrolController::State::patrol;
			}
			AICon->MoveToLocation(AICon->LastLocation);
			return EBTNodeResult::Succeeded;
		}

		
		//AICon->ReceiveMoveCompleted;
	}


	//just in case
	return EBTNodeResult::Failed;

}