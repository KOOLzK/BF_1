// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "BTSelectPatrolPoint.h"
#include "AIPatrolPoint.h"
#include "AIPatrolController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTSelectPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwerComp, uint8* NodeMemory)
{
	AAIPatrolController* AICon = Cast<AAIPatrolController>(OwerComp.GetAIOwner());

	if(AICon)
	{
		//old i don't know if i still need this
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
		//old i don't know if i still need this
		AAIPatrolPoint* CurrentPoint = Cast<AAIPatrolPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));

		TArray<AActor*> AvailablePatrolPoints = AICon->GetPatrolPoints();

		/*i don't know if i still need NextPatrolPoint cause its using BlackboardComp and i don't 
		think i'm using Black boards any more*/
		AAIPatrolPoint* NextPatrolPoint = nullptr;
		if (AICon->GetMoveStatus() == EPathFollowingStatus::Idle) {
			if (AICon->CurrentPatrolPoint != AvailablePatrolPoints.Num() - 1)
			{
				AICon->CurrentPatrolPoint++;
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::FromInt(AICon->CurrentPatrolPoint));
				NextPatrolPoint = Cast<AAIPatrolPoint>(AvailablePatrolPoints[AICon->CurrentPatrolPoint]);
			}
			else
			{
				NextPatrolPoint = Cast<AAIPatrolPoint>(AvailablePatrolPoints[0]);
				AICon->CurrentPatrolPoint = 0;
			}
		}
		//old i don't know if i still need this
		BlackboardComp->SetValueAsObject("LocationToGo", NextPatrolPoint);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;

}




