// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "BTService_CheckLights.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AIPatrol.h"
#include "AIPatrolController.h"



UBTService_CheckLights::UBTService_CheckLights() {
	bCreateNodeInstance = true;
}

void UBTService_CheckLights::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {

	AAIPatrolController* AICon = Cast<AAIPatrolController>(OwnerComp.GetAIOwner());

	if (AICon)
	{
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
		BlackboardComp->SetValueAsBool("True", true);
		AAIPatrol* AICharacter = Cast<AAIPatrol>(AICon->GetPawn());

		float light;
		light = AICharacter->GetLightingAmount();

		if (light == 0) {
			//BlackboardComp->SetValueAsBool("IsInLight", false);
			AICharacter->GetCharacterMovement()->MaxWalkSpeed = AICharacter->MyMaxWalkSpeed;
		}
		else {
			//BlackboardComp->SetValueAsBool("IsInLight", true);
			//AICharacter->SetActorLocation(AICharacter->GetActorLocation());
			AICharacter->GetCharacterMovement()->MaxWalkSpeed = 0;
		}

	}

}