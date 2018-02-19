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
			//AICon->MovingToLocationMakerOff();
			//when Idle it moves to the next Patrol Point and when it has completed the move it goes Idle
			if (AICon->GetMoveStatus() == EPathFollowingStatus::Idle)
			{
				AICon->MoveToActor(NextPatrolPoint, 5.f, true, true, true, 0, true);
				
				/*SpinDone = false;
				BackFromSearch = false;
				StartNotSet = true;*/

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
				//getplayers forward vector
				//Playerforward = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
			}
			AICon->ResetMovingToLocationMaker();
			AICon->MoveToLocation(AICon->LastLocation);
			return EBTNodeResult::Succeeded;
		}

		if (AICon->CurrentState == AAIPatrolController::State::lastSeen) {
			AICon->ResetMovingToLocationMaker();
			if (AICon->GetMoveStatus() == EPathFollowingStatus::Idle)
			{
				AICon->MovingToLocationMakerOff();
				AICon->CurrentState = AAIPatrolController::State::patrol;
				/*go to search pattern instead of patrol
				use players LastLocation and forward vector to do a raycast then uses the location
				to give to search pattern*/
				//Ray Trace
				/*HitResult = new FHitResult();
				StartTrace = AICon->LastLocation;
				ForwardVector = Playerforward;
				EndTrace = ((ForwardVector * 1000) + StartTrace); //1000 is to far?
				TraceParams = new FCollisionQueryParams();

				if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECollisionChannel::ECC_WorldStatic, *TraceParams))
				{
					SearchLocation = HitResult->Location;
				}*/
			}
			//EPathFollowingResult 
			//EPathFollowingResult::Invalid;
			
			//AICon->OnMoveCompleted(AICon->GetCurrentMoveRequestID(), EPathFollowingResult::Invalid);
			/*if (AICon->GetMoveStatus() == EPathFollowingResult::Blocked) {
				AICon->MovingToLocationMakerOff();
			}*/
			AICon->MoveToLocation(AICon->LastLocation);
			return EBTNodeResult::Succeeded;
		}

		//add searching and think of a were to have a search pattern
		/*if (AICon->CurrentState == AAIPatrolController::State::searching) {
			if (AICon->GetMoveStatus() == EPathFollowingStatus::Idle)
			{
				if (BackFromSearch) {
					AICon->CurrentState = AAIPatrolController::State::patrol;
					AICon->MovingToLocationMakerOff();
				} else {
					if (SpinDone) {
						BackFromSearch = true;
					} else {
						if (StartNotSet) {
							RotationStart = AICon->GetPawn()->GetActorRotation();
							StartNotSet = false;
						} else {
							if (RotationStart.Yaw +5 >= AICon->GetPawn()->GetActorRotation().Yaw && RotationStart.Yaw - 5 <= AICon->GetPawn()->GetActorRotation().Yaw) {
								SpinDone = true;
							} else {
								AICon->AddActorLocalRotation(FQuat(0.0f, 0.0f, 0.01f, 1.0f));
							}
						}
						
					}
					AICon->MoveToLocation(SearchLocation);
				}
				
				//AICon->AddActorLocalRotation(FQuat(0.0f,0.0f,1.0f,1.0f));
			}
			AICon->MoveToLocation(SearchLocation);
			return EBTNodeResult::Succeeded;
		}*/
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