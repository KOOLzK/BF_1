// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "PlayerCharacter.h"
#include "EnemyAI.h"
#include "EnemyCharacter.h"
#include "BTTask_MoveToPlayer.h"


EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	AEnemyAI *CharPC = Cast<AEnemyAI>(OwnerComp.GetAIOwner());

	APlayerCharacter *Enemy = Cast<APlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(CharPC->EnemyKeyID));

	if (Enemy) {
		CharPC->MoveToActor(Enemy, 5.f, true, true, true, 0, true);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed; 
	}
	/*//unnesary
	FNavLocation NavLoc;
	if (GetWorld()->GetNavigationSystem()->ProjectPointToNavigation(Enemy->GetActorLocation(), NavLoc)) {//(CharPC->GetActorLocation, Enemy);
		//CharPC->resetEnemyLocation();
		//CharPC->SetActorLocation(CharPC->possesedEnemy->)
	}*/
	//CharPC->resetEnemyLocation();
	EBTNodeResult::Failed;
}

