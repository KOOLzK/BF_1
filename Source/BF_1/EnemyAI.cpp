// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyCharacter.h"
#include "EnemyAI.h"


AEnemyAI::AEnemyAI() {
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
}

void AEnemyAI::Possess(APawn *InPawn) {
	Super::Possess(InPawn);
	/*//unnesary
	possesedEnemy = InPawn;
	*/
	AEnemyCharacter *Char = Cast<AEnemyCharacter>(InPawn);

	if (Char && Char->BotBehavior) {
		BlackboardComp->InitializeBlackboard(*Char->BotBehavior->BlackboardAsset);

		EnemyKeyID = BlackboardComp->GetKeyID("Target");

		BehaviorComp->StartTree(*Char->BotBehavior);
	}
}

/*//unnesary
void AEnemyAI::resetEnemyLocation() {
	AEnemyCharacter *Char = Cast<AEnemyCharacter>(possesedEnemy);
	Char->SetActorLocation(Char->startLocation);
}*/
