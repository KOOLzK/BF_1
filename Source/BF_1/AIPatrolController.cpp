// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "AIPatrolController.h"
#include "AIPatrol.h"
#include "AIPatrolPoint.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AAIPatrolController::AAIPatrolController()
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	PlayerKey = "Target";
	LocationToGoKey = "LocationToGoKey";

	CurrentPatrolPoint = 0;
}

void AAIPatrolController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	AAIPatrol* AICharacter = Cast<AAIPatrol>(Pawn);

	if (AICharacter) {

		if (AICharacter->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
		}

		/*change to get form AICharacter*/
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIPatrolPoint::StaticClass(), AllPoints);

		for (int i = 0; i < AllPoints.Num(); i++) {
			AAIPatrolPoint* temp = Cast<AAIPatrolPoint>(AllPoints[i]);
			if (AICharacter->enemyName == temp->enemyName) {
				PatrolPoints.Add(temp);
			}
		}
		if (PatrolPoints.Num() > 0) {
			BehaviorComp->StartTree(*AICharacter->BehaviorTree);
		}
	}
}

void AAIPatrolController::SetPlayerCaught(APawn* Pawn)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(PlayerKey, Pawn);
	}
}