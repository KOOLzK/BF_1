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
	//old i don't know if i still need this
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	PlayerKey = "Target";
	LocationToGoKey = "LocationToGoKey";

	CurrentPatrolPoint = 0;

	lastSeenTimer = 10;

	Result = false;
	AllResult = false;
}

void AAIPatrolController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	CurrentState = State::patrol;

	AICharacterRef = Pawn;

	AAIPatrol* AICharacter = Cast<AAIPatrol>(Pawn);

	if (AICharacter) {

		if (AICharacter->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
		}

		/*change to get form AICharacter << I don't remember what that ment*/    /*gets all AIPatrolPoint in the level*/
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIPatrolPoint::StaticClass(), AllPoints);
			

		/*checks to see if the Patrol Point belongs to this enemy*/
		for (int i = 0; i < AllPoints.Num(); i++) {
			AAIPatrolPoint* temp = Cast<AAIPatrolPoint>(AllPoints[i]);
			if (AICharacter->enemyName == temp->enemyName) {
				PatrolPoints.Add(temp);
			}
		}
		//PatrolPoints.Sort
		//orders the Patrol Points lowest to highest or the other i don't remember
		do {
			AllResult = false;
			for (int i = 0; i + 1 < PatrolPoints.Num(); i++) {
				AAIPatrolPoint* temp = Cast<AAIPatrolPoint>(PatrolPoints[i]);
				AAIPatrolPoint* temp2 = Cast<AAIPatrolPoint>(PatrolPoints[i + 1]);

				if (temp->Order > temp2->Order) {
					PatrolPoints.RemoveAt(i);
					PatrolPoints.Insert(temp, i + 1);
					Result = true;
				}
				if (Result) {
					AllResult = true;
				}
				Result = false;
			}
		} while (AllResult);

		if (PatrolPoints.Num() > 0) {
			BehaviorComp->StartTree(*AICharacter->BehaviorTree);
		}

		MovingToLocationMakerOff();
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Begin2222");
}

void AAIPatrolController::SetPlayerCaught(APawn* Pawn)
{
	lastSeenTimer = 10;
	if (CurrentState == State::lastSeen) {
		MovingToLocationMakerOff();
	}
	CurrentState = State::spotted;

	LastLocation = Pawn->GetActorLocation();
}

//Particle System On
void AAIPatrolController::MovingToLocationMakerOn() 
{
	AAIPatrol* AICharacter = Cast<AAIPatrol>(AICharacterRef);

	ResetMovingToLocationMaker();

	//AICharacter->MovingToLocationMaker->ActivateSystem();
	AICharacter->MovingToLocationMaker->Activate();
	//AICharacter->MovingToLocationMaker->bSuppressSpawning = true;
}
//Particle System Off
void AAIPatrolController::MovingToLocationMakerOff()
{
	AAIPatrol* AICharacter = Cast<AAIPatrol>(AICharacterRef);

	//AICharacter->MovingToLocationMaker->DeactivateSystem();bSupressSpawning
	AICharacter->MovingToLocationMaker->Deactivate();
	//AICharacter->MovingToLocationMaker->bSuppressSpawning = false;
}

void AAIPatrolController::ResetMovingToLocationMaker()
{
	AAIPatrol* AICharacter = Cast<AAIPatrol>(AICharacterRef);
	AICharacter->MovingToLocationMaker->SetWorldLocation(LastLocation);
}


/*  
Ref
https://answers.unrealengine.com/questions/158065/startstop-emitting-particle-system-component.html


crap

//UE_LOG(LogTemp, Warning, TEXT("one"));

//for (int i = 0; i < AllPoints.Num(); i++) {
//	AAIPatrolPoint* temp = Cast<AAIPatrolPoint>(AllPoints[i]);
//	UE_LOG(LogTemp, Warning, TEXT("two"));
//	/*checks to see if the Patrol Point belongs to this enemy*
//	if (AICharacter->enemyName == temp->enemyName) {
//		UE_LOG(LogTemp, Warning, TEXT("three"));
//		/*if so puts them in order*
//		if (PatrolPoints.Num() > 0) {
//			UE_LOG(LogTemp, Warning, TEXT("four"));
//			/*if PatrolPoints has at least one point*
//			for (int j = 0; j < PatrolPoints.Num(); j++) {
//				AAIPatrolPoint* temp2 = Cast<AAIPatrolPoint>(PatrolPoints[j]);
//				UE_LOG(LogTemp, Warning, TEXT("five"));
//				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(j));
//				/*orders the next one in where it is lower*
//				if (temp->Order < temp2->Order) {
//					//PatrolPoints.Insert(temp, j);
//					UE_LOG(LogTemp, Warning, TEXT("six"));
//				} else {
//					UE_LOG(LogTemp, Warning, TEXT("seven"));
//					/*if the next one is the highest number add to end*
//					PatrolPoints.Add(temp);
//				}
//			}
//		} else {
//			UE_LOG(LogTemp, Warning, TEXT("eight"));
//			/*if PatrolPoints is empty just add it in*
//			PatrolPoints.Add(temp);
//		}
//		//PatrolPoints.Add(temp);
//	}
//}


/*for (int i = 0; i < PatrolPoints.Num(); i++) {
AAIPatrolPoint* temporary = Cast<AAIPatrolPoint>(PatrolPoints[i]);
//FString::FromInt(temporary->Order);
GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::FromInt(temporary->Order));
}*

/*for (int i = 0; i < PatrolPoints.Num(); i++) {
AAIPatrolPoint* temporary = Cast<AAIPatrolPoint>(PatrolPoints[i]);
//FString::FromInt(temporary->Order);
GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::FromInt(temporary->Order));
}*

/*void AAIPatrolController::SetPlayerLost(APawn* Pawn)
{
CurrentState = State::lastSeen;

LastLocation = Pawn->GetActorLocation();

}*
*/