// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "AIPatrolController.generated.h"

/**
 * 
 */
UCLASS()
class BF_1_API AAIPatrolController : public AAIController
{
	GENERATED_BODY()

	UBehaviorTreeComponent* BehaviorComp;

	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	FName LocationToGoKey;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	FName PlayerKey;

	//Patrol Points that will be used
	TArray<AActor*> AllPoints;

	//Patrol Points for this enemy
	TArray<AActor*> PatrolPoints;

	/*//current target location
	AActor* Target;*/

	virtual void Possess(APawn* Pawn) override;

	bool Result;

	bool AllResult;

public:

	AAIPatrolController();

	void SetPlayerCaught(APawn* Pawn);

	//void SetPlayerLost(APawn* Pawn);

	/*places a Particle System where the enemy last saw the player*/
	void MovingToLocationMakerOn();

	/*removes the Particle System where the enemy last saw the player*/
	void MovingToLocationMakerOff();

	int32 CurrentPatrolPoint = 0;

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; }
	

	/*Patrol moving between patrol points.
	Spotted the enemy sees the player.
	LastSeen enemy moves to the place the player was last seen.
	Searching enemy has gone to the place where the player was last seen and didn't find the player. */
	enum State { patrol, spotted, lastSeen, searching };

	State CurrentState;

	FVector LastLocation;

	int32 lastSeenTimer;

	APawn* AICharacterRef;
};
