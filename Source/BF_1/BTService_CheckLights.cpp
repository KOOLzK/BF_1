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

			//maybe this should be a function in AIPatrol and this just calls it

			//if the enemy is set to be invisible in the dark then make it invisible
			if (AICharacter->HeadInvisibleInDark) {
				AICharacter->Head->SetMaterial(0, AICharacter->SeeThroughMaterial);
			}
			if (AICharacter->BodyInvisibleInDark) {
				AICharacter->Body->SetMaterial(0, AICharacter->SeeThroughMaterial);
			}

			//let enemy move
			AICharacter->GetCharacterMovement()->MaxWalkSpeed = AICharacter->MyMaxWalkSpeed;

			//play walking sound
			if (!AICharacter->propellerAudioComponent->IsPlaying())
			{
				AICharacter->propellerAudioComponent->Play();
			}

			/*Spawns Foot Print when enemies walk. Note Location is lowered in the z axis to get it 
			close enough to the ground to spawn, if enemy height changes this z axis will have to too.
			Note Rotaton was changed in the Roll because Foot Print picture was the wrong way, if we 
			get a different one check this*/
			UGameplayStatics::SpawnDecalAtLocation(GetWorld(), AICharacter->FootPrintMaterial, FVector(50, 50, 50), AICharacter->GetActorLocation() - FVector(0,0,80), FRotator(-90, AICharacter->GetActorRotation().Yaw, AICharacter->GetActorRotation().Roll + 90), 5.0f);


			//set animtions / Poses
			/*AICharacter->AnimationToggle = !AICharacter->AnimationToggle;
			if (AICon->CurrentState == AAIPatrolController::State::patrol) {
				AICharacter->AnimationNumber = 0;
			}else if (AICon->CurrentState == AAIPatrolController::State::spotted) {
				AICharacter->AnimationNumber = 1;
			}*/ //moved to AIPatrol


			//call animation
			AICharacter->AnimationPoses();
		}
		else {
			//BlackboardComp->SetValueAsBool("IsInLight", true);
			//AICharacter->SetActorLocation(AICharacter->GetActorLocation());

			//if the enemy is set to be invisible in the dark then make it visible in the light
			if (AICharacter->HeadInvisibleInDark) {
				AICharacter->Head->SetMaterial(0, AICharacter->HeadMaterial);
			}
			if (AICharacter->BodyInvisibleInDark) {
				AICharacter->Body->SetMaterial(0, AICharacter->BodyMaterial);
			}

			//stop enemy from moving
			AICharacter->GetCharacterMovement()->MaxWalkSpeed = 0;

			//stop walking sound
			AICharacter->propellerAudioComponent->Stop();

			//
			AICharacter->LightUpdate = true;
		}

	}

}