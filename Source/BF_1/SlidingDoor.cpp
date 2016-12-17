// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "SlidingDoor.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"


// Sets default values
ASlidingDoor::ASlidingDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CoiComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("SlidingDoor");
	RootComponent = CollisionComp;

	DoorMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->AttachTo(RootComponent);

	/*ClosedPosition = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("ClosedPosition"));
	ClosedPosition->SetRelativeLocation(FVector(0, 100, 0));*/
	//ClosedPosition->AttachTo(RootComponent);

	/*OpenedPosition = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("OpenedPosition"));
	OpenedPosition->SetRelativeLocation(FVector(0, -100, 0));*/
	//OpenedPosition->AttachTo(RootComponent);

	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	LightKey = "Light";
	speed = 10.0f;

	DY = 0;
	ClosedY = 0;
	OpenedY = 10;
}

// Called when the game starts or when spawned
void ASlidingDoor::BeginPlay()
{
	Super::BeginPlay();

	BlackboardComp->InitializeBlackboard(*(BehaviorTree->BlackboardAsset));
	
}

// Called every frame
void ASlidingDoor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	DY = DoorMesh->RelativeLocation.Y;
	/*CY = ClosedPosition->GetComponentLocation().Y;
	OY = OpenedPosition->GetComponentLocation().Y;*/

	if (BlackboardComp->GetValueAsBool(LightKey)) {
		if (DY < ClosedY)
		{
			DoorMesh->SetRelativeLocation(FVector(DoorMesh->RelativeLocation.X, DoorMesh->RelativeLocation.Y + speed, DoorMesh->RelativeLocation.Z));
		}
	}
	else
	{
		if (DY > OpenedY)
		{
			DoorMesh->SetRelativeLocation(FVector(DoorMesh->RelativeLocation.X, DoorMesh->RelativeLocation.Y - speed, DoorMesh->RelativeLocation.Z));
		}
	}

}

