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

	int32 CurrentPatrolPoint = 0;

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; }
	
};
