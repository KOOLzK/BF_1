// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "PhysicsInteract.h"


// Sets default values  /// change to SpherePhysics
APhysicsInteract::APhysicsInteract()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CoiComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("PhysicsInteract");
	CollisionComp->SetCollisionResponseToChannel(EEC_InteractAble, ECollisionResponse::ECR_Block);
	CollisionComp->SetSimulatePhysics(true);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = CollisionComp;

	InteractAbleMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("InteractAbleMesh"));
	InteractAbleMesh->SetRelativeLocation(FVector(0, 0, 0));
	InteractAbleMesh->SetCollisionResponseToChannel(EEC_InteractAble, ECollisionResponse::ECR_Block);
	InteractAbleMesh->AttachTo(CollisionComp);
}

// Called when the game starts or when spawned
void APhysicsInteract::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APhysicsInteract::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APhysicsInteract::Focused()
{
	//mesh->SetRenderCustomDepth(true);
	InteractAbleMesh->SetRenderCustomDepth(true);
}

void APhysicsInteract::Unfocused()
{
	//mesh->SetRenderCustomDepth(false);
	InteractAbleMesh->SetRenderCustomDepth(false);
}
