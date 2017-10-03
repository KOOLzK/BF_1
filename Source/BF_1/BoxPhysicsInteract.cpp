// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "BoxPhysicsInteract.h"


// Sets default values  
ABoxPhysicsInteract::ABoxPhysicsInteract()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CoiComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("PhysicsInteract");
	CollisionComp->SetCollisionResponseToChannel(EEC_InteractAble, ECollisionResponse::ECR_Block);
	CollisionComp->SetSimulatePhysics(true);
	HasPhysics = true;
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = CollisionComp;

	InteractAbleMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("InteractAbleMesh"));
	InteractAbleMesh->AttachTo(CollisionComp);

	ZLevelRespone = -10000;
}

// Called when the game starts or when spawned
void ABoxPhysicsInteract::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}

// Called every frame
void ABoxPhysicsInteract::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetActorLocation().Z < ZLevelRespone)
	{
		SetActorLocation(StartLocation);
		CollisionComp->SetPhysicsLinearVelocity(FVector(0, 0, 0));
	}
}

void ABoxPhysicsInteract::Focused()
{
	InteractAbleMesh->SetRenderCustomDepth(true);
}

void ABoxPhysicsInteract::Unfocused()
{
	InteractAbleMesh->SetRenderCustomDepth(false);
}

void ABoxPhysicsInteract::AttachToHead(USceneComponent* Head)
{
	CollisionComp->SetSimulatePhysics(false);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	CollisionComp->AttachToComponent(Head, FAttachmentTransformRules::KeepWorldTransform);
}

void ABoxPhysicsInteract::DetachFromHead()
{
	CollisionComp->DetachFromParent(true);
	CollisionComp->SetSimulatePhysics(true);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

