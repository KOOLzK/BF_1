// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PowerGirdHookUp.h"
#include "PO_Gate.generated.h"


/*UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EGateEnum : uint8
{
	GE_And 	UMETA(DisplayName = "AndGate"),
	GE_Or 	UMETA(DisplayName = "OrGate"),
	GE_Not	UMETA(DisplayName = "NotGate")
};*/


UCLASS()
class BF_1_API APO_Gate : public APowerGirdHookUp
{
	GENERATED_BODY()


public:
	APO_Gate();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
};
