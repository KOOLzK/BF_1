// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PG_Observer.generated.h"

UCLASS()
class BF_1_API APG_Observer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APG_Observer();// PG_Subject *mod, bool div);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//i don't know what my name convention is
	class PG_Subject *model;
	bool denom;

	//I feel like this is supposed to be the constructor  
	void Observer(PG_Subject *mod, bool div);
	
	virtual void Update();

	//doesn't bellog here but testing
	//class PowerObject* PO;

protected:
	PG_Subject *getSubject();

	bool getDivisor();

};
