// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "StaticInteract.h"



// Sets default values  /// change to SpherePhysics
AStaticInteract::AStaticInteract()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CoiComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("StaticInteract");
	CollisionComp->SetCollisionResponseToChannel(EEC_InteractAble, ECollisionResponse::ECR_Block);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = CollisionComp;

	HasPhysics = false;

	InteractAbleMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("InteractAbleMesh"));
	InteractAbleMesh->AttachTo(CollisionComp);
}

// Called when the game starts or when spawned
void AStaticInteract::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AStaticInteract::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStaticInteract::Focused()
{
	//mesh->SetRenderCustomDepth(true);
	InteractAbleMesh->SetRenderCustomDepth(true);
}

void AStaticInteract::Unfocused()
{
	//mesh->SetRenderCustomDepth(false);
	InteractAbleMesh->SetRenderCustomDepth(false);
}