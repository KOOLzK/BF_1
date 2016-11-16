// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LightManager.generated.h"

UCLASS()
class BF_1_API ALightManager : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Light)
	FName LightKey;
	
public:	
	// Sets default values for this actor's properties
	ALightManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//UPROPERTY(EditAnywhere, Category = Light)
	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditAnywhere, Category = Light)
	class UBehaviorTree* BehaviorTree;

	FTimerHandle lightDelay;

	void toggle();

	bool Light;
	
};
