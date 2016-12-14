// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TargetPoint.h"
#include "AIPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class BF_1_API AAIPatrolPoint : public ATargetPoint
{
	GENERATED_BODY()
	
public:
	/*UPROPERTY(EditAnywhere, Category = AI)
	FString o;*/

	/*Is used for selecting the Enemy with the same Name*/
	UPROPERTY(EditAnywhere, Category = AI)
	FName enemyName;

	/*Is used to order the points*/
	UPROPERTY(EditAnywhere, Category = AI)
	int Order;
	
};
