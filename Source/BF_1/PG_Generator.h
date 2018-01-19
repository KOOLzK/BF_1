// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PowerGirdHookUp.h"
#include "PG_Generator.generated.h"

/**
 * 
 */
UCLASS()
class BF_1_API APG_Generator : public APowerGirdHookUp
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APG_Generator();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
};
