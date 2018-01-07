// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "PhysicsInteract.h"

// change to SpherePhysics, [currently being used for Bouncy ball and Key, 02/09/2017]

// change name to InteractSphere 05/01/2018

// Sets default values  
APhysicsInteract::APhysicsInteract()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CoiComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("PhysicsInteract");
	CollisionComp->SetCollisionResponseToChannel(EEC_InteractAble, ECollisionResponse::ECR_Block);
	
	HasPhysics = false;
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = CollisionComp;

	InteractAbleMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("InteractAbleMesh"));
	//InteractAbleMesh->SetRelativeLocation(FVector(0, 0, 0));
	//InteractAbleMesh->SetCollisionResponseToChannel(EEC_InteractAble, ECollisionResponse::ECR_Block);
	InteractAbleMesh->AttachTo(CollisionComp);

	ZLevelRespone = -10000;

	HandSize = 0;
}

// Called when the game starts or when spawned
void APhysicsInteract::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();//CollisionComp->GetComponentLocation();
	CollisionComp->SetSimulatePhysics(HasPhysics);

	if (HandSize == 0) {
		isHanded = Handed::Small;
	} else {
		isHanded = Handed::Medium;
	}

}

// Called every frame
void APhysicsInteract::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetActorLocation().Z < ZLevelRespone)
	{
		SetActorLocation(StartLocation);
		CollisionComp->SetPhysicsLinearVelocity(FVector(0, 0, 0));
	}
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

void APhysicsInteract::AttachToHead(USceneComponent* Head)
{
	//this->AddOwnedComponent(Head);
	//this->AttachToComponent
	CollisionComp->SetSimulatePhysics(false);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);// :NoCollision);//:PhysicsOnly);//QueryOnly
	//CollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	//CollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Ignore);
	//CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionComp->AttachToComponent(Head, FAttachmentTransformRules::KeepWorldTransform);
}

void APhysicsInteract::DetachFromHead()
{
	CollisionComp->DetachFromParent(true);
	//CollisionComp->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	CollisionComp->SetSimulatePhysics(true);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//CollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	//CollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	//CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	/*CollisionComp->AttachToComponent(Head, FAttachmentTransformRules::KeepWorldTransform);*/
}

void APhysicsInteract::Throw(FVector Direction)
{
	CollisionComp->AddForce(Direction);
}