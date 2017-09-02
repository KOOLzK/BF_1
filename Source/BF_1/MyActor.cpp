// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "MyActor.h"

//This is the BlinkingLight i don't remember why it is called MyActor

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DesiredIntensity = 3000.0f;

	PointLight1 = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight1"));
	PointLight1->Intensity = 0.f;
	PointLight1->bVisible = true;
	RootComponent = PointLight1;
	temp2 = true;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(lightDelay, this, &AMyActor::toggle, 1.f, true);
}

// Called every frame
void AMyActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AMyActor::toggle() {
	temp2 = !temp2;
	PointLight1->SetVisibility(temp2);
}

/*
Ref

crap

//DesiredIntensity;


//GetWorldTimerManager().SetTimer(this, &AMyActor::toggle, 5.f, false);
//GetWorldTimerManager().SetTimer(lightDelay, this, &AMyActor::toggle, 5.f, false);
//GetWorldTimerManager().SetTimer(lightDelay, &AMyActor::toggle, 5.f,true, 0.0f);
//GetWorldTimerManager().SetTimer(lightDelay, this, &AMyActor::toggle, 1.0f, true);

//temp += 10;
//temp = cos(DeltaTime);
//PointLight1->Intensity = temp;// *DesiredIntensity;
//PointLight1->SetWorldLocation(FVector(temp, 10, 0));
/*if (temp2) {
temp2 = false;
}*
//PointLight1->SetIntensity(temp);

//PointLight1->bVisible = false;
//PointLight1->ComputeLightBrightness.bVisible = temp2;


//GetWorldTimerManager().SetTimer(lightDelay, this, &AMyActor::toggle, 5.f, false);
*/