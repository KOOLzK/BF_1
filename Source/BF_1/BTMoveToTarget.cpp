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

		//States of the enemy
		if (AICon->CurrentState == AAIPatrolController::State::patrol) {

			//when Idle it moves to the next Patrol Point and when it has completed the move it goes Idle
			if (AICon->GetMoveStatus() == EPathFollowingStatus::Idle)
			{
				AICon->MoveToActor(NextPatrolPoint, 5.f, true, true, true, 0, true);
				
				return EBTNodeResult::Succeeded;
			}
		}

		if (AICon->CurrentState == AAIPatrolController::State::spotted) {
			//lastSeenTimer is so the BehaviorTree isn't constantly resetting the State and Particle System
			/*i think i need this but maybe not and i don't know if there is a better way
			becasue i think the enemy will not turn to track the player as they move sideways or go 
			past the player then snap to them only to do it over again*/
			AICon->lastSeenTimer--;
			if (AICon->lastSeenTimer < 0) {
				AICon->CurrentState = AAIPatrolController::State::lastSeen;
				AICon->MovingToLocationMakerOn();
			}
			AICon->MoveToLocation(AICon->LastLocation);
			return EBTNodeResult::Succeeded;
		}

		if (AICon->CurrentState == AAIPatrolController::State::lastSeen) {
			if (AICon->GetMoveStatus() == EPathFollowingStatus::Idle)
			{
				AICon->CurrentState = AAIPatrolController::State::patrol;
				AICon->MovingToLocationMakerOff();
			}
			AICon->MoveToLocation(AICon->LastLocation);
			return EBTNodeResult::Succeeded;
		}

		//add searching and think of a were to have a search pattern
	}


	//just in case
	return EBTNodeResult::Failed;

}

/*
Ref

crap

//if (AICon->GetCurrentMoveRequestID().IsValid)//IsEquivalent;//MoveToActor.GetCurrentMoveRequestID();
//if (AICon->GetMoveStatus()); //AICon->GetMoveGoalReachTest(AICon, , NextPatrolPoint, 5.f, 5.f

//if(AICon->GetPawn()->GetDistanceTo(NextPatrolPoint) < 10.1f)

//EPathFollowingStatus::Moving;
//AICon->GetMoveGoalOffset(AICon);

//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::FromInt(AICon->CurrentPatrolPoint));

else { //for if (AICon->GetMoveStatus() == EPathFollowingStatus::Idle)
//return EBTNodeResult::InProgress;
}

//AICon->ReceiveMoveCompleted;

*/