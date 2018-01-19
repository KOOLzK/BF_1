// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "ActorRespone.h"


// Sets default values
AActorRespone::AActorRespone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShapeMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("CoiComp"));
	ShapeMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	RootComponent = ShapeMesh;

	ZLevelRespone = -10000;
}

// Called when the game starts or when spawned
void AActorRespone::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
}

// Called every frame
void AActorRespone::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (GetActorLocation().Z < ZLevelRespone)
	{
		SetActorLocation(StartLocation);
		ShapeMesh->SetPhysicsLinearVelocity(FVector(0, 0, 0));
	}
}

