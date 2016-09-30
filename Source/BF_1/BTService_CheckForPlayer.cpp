// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"//player Charactor 20:00

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "PlayerCharacter.h"
#include "EnemyAI.h"
#include "EnemyCharacter.h"
#include "BTService_CheckForPlayer.h"


UBTService_CheckForPlayer::UBTService_CheckForPlayer() {
	bCreateNodeInstance = true;
}

void UBTService_CheckForPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	AEnemyAI *EnemyPC = Cast<AEnemyAI>(OwnerComp.GetAIOwner());

	if (EnemyPC) {
		APlayerCharacter *Enemy = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

		if (Enemy) {
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(EnemyPC->EnemyKeyID, Enemy);
			//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "ENEMY IS HERE");
		}
		//OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>("Light", true);
	}

	
}