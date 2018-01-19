// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PowerGirdHookUp.h"
#include "PG_Timer.generated.h"

/**
 * 
 */
UCLASS()
class BF_1_API APG_Timer : public APowerGirdHookUp
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APG_Timer();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	
	void toggle();

	UPROPERTY(EditAnywhere, Category = Light)
	float DelayLight;

	FTimerHandle lightDelay;
};
