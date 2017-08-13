// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "InteractAble.h"




// Sets default values
AInteractAble::AInteractAble()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//BodyInstance.SetCollisionProfileName
	//CollisionComp->BodyInstance.SetCollisionProfileName("InteractAbleCollisionComp");
	//CollisionComp->SetCollisionResponseToChannel(EEC_InteractAble, ECollisionResponse::ECR_Block);

	//InteractAbleMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("InteractAbleMesh"));
	//InteractAbleMesh->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AInteractAble::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractAble::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AInteractAble::Focused() 
{
	//mesh->SetRenderCustomDepth(true);
	//InteractAbleMesh->SetRenderCustomDepth(true);
}

void AInteractAble::Unfocused()
{
	//mesh->SetRenderCustomDepth(false);
	//InteractAbleMesh->SetRenderCustomDepth(false);
}

void AInteractAble::AttachToHead(USceneComponent* Head)
{

}

void AInteractAble::DetachFromHead()
{

}