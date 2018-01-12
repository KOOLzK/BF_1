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

	/*if (HandSize == 0) {
		isHanded = EHandedEnum::HE_Small;
	} else {
		isHanded = EHandedEnum::HE_Medium;
	}*/

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
	//it is set to PhysicsOnly so it has doesn't have Query so you can't pick it again
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);// :NoCollision);//:PhysicsOnly);//QueryOnly
	//so it doesn't push the player around
	InteractAbleMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	CollisionComp->AttachToComponent(Head, FAttachmentTransformRules::KeepWorldTransform);
	Held = true;
}

void APhysicsInteract::DetachFromHead()
{
	CollisionComp->DetachFromParent(true);
	CollisionComp->SetSimulatePhysics(true);
	//it is set to QueryAndPhysics so it has Query so you can pick it later
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//so the player can push it around and stand on it
	InteractAbleMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	Held = false;
}

void APhysicsInteract::Throw(FVector Direction)
{
	if (!Held)
	CollisionComp->AddForce(Direction);
	//CollisionComp->AddImpulse(Direction);
}

void APhysicsInteract::ZeroVelocity()
{
	CollisionComp->SetPhysicsLinearVelocity(FVector(0, 0, 0));
}

void APhysicsInteract::DampenVelocity(float DampenBy)
{
	if (GetVelocity().Size() > 1.0f) {
		CollisionComp->SetPhysicsLinearVelocity(FVector(GetVelocity().X / DampenBy, GetVelocity().Y / DampenBy, GetVelocity().Z));
	} /*else {
		//it keeps moving slowly and i don't like that
		CollisionComp->SetPhysicsLinearVelocity(FVector(0, 0, 0));
		CollisionComp->SetPhysicsAngularVelocity(FVector(0, 0, 0));
		//CollisionComp->stop
		//UMovementComponent::sto
		//CollisionComp->MoveComponent.
	}*/
}