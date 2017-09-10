// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "StaticInteract.h"


// change to BoxStatic, [currently being used for door, 02/09/2017]


// Sets default values  
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

void AStaticInteract::UpdateAndDelete()
{
	CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionComp->AddWorldTransform(FTransform(FVector(0, 0, 1.0f)));//FVector(0, 0, 1.0f));
	CollisionComp->UpdateNavigationBounds();
	this->Destroy();
}