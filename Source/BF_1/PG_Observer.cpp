// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "PG_Observer.h"
#include "PG_Subject.h"

// Sets default values
APG_Observer::APG_Observer()//PG_Subject *mod, bool div)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*model = mod;
	denom = div;

	model->Attach(this);*/
}

// Called when the game starts or when spawned
void APG_Observer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APG_Observer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void APG_Observer::Observer(PG_Subject *mod, bool div)
{
	model = mod;
	denom = div;
	
	model->Attach(this);
}

/*PG_Subject APG_Observer::*getSubject()
{
}*/

PG_Subject * APG_Observer::getSubject()
{
	return model;
}


bool APG_Observer::getDivisor()
{
	return denom;
}

void APG_Observer::Update()
{
	//it won't compile if this isn't here
}