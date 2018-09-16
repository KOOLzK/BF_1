// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "InteractSphere.h"


// Sets default values  
AInteractSphere::AInteractSphere()
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
	//InteractAbleMesh->AttachTo(CollisionComp);
	InteractAbleMesh->SetupAttachment(CollisionComp);

	ZLevelRespone = -10000;

	AttachDistence = 100;
}

// Called when the game starts or when spawned
void AInteractSphere::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();//CollisionComp->GetComponentLocation();
	CollisionComp->SetSimulatePhysics(HasPhysics);
}

// Called every frame
void AInteractSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetActorLocation().Z < ZLevelRespone)
	{
		SetActorLocation(StartLocation);
		CollisionComp->SetPhysicsLinearVelocity(FVector(0, 0, 0));
	}

	//all of this was tril and error so i don't know all of what its doing
	if (Attach != NULL) {
		float dis = Attach->GetDistanceTo(this);

		if (Attach->IsA(AInteractAble::StaticClass())) {
			AInteractAble* temp = Cast<AInteractAble>(Attach);

			if (dis > AttachDistence) {
				FVector idk = GetActorLocation() - Attach->GetActorLocation();

				if (temp->Held) {
					ACharacter* cc = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
					cc->AddMovementInput(idk, 1.0f);

				} else {
					temp->Throw(idk * (idk.Size() / 2));
					temp->LastFrameOutOfBounds = true;
				}

			} else { 
				temp->DampenVelocity(1.1f);
			}
		}
	}
}

void AInteractSphere::Focused()
{
	InteractAbleMesh->SetRenderCustomDepth(true);
}

void AInteractSphere::Unfocused()
{
	InteractAbleMesh->SetRenderCustomDepth(false);
}

void AInteractSphere::AttachToHand(USceneComponent* Hand)
{
	CollisionComp->SetSimulatePhysics(false);

	//it is set to PhysicsOnly so it has doesn't have Query so you can't pick it again
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	//so it doesn't push the player around
	InteractAbleMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	
	CollisionComp->AttachToComponent(Hand, FAttachmentTransformRules::KeepWorldTransform);
	Held = true;
}

void AInteractSphere::DetachFromHand() // AInteractAble* MakeHandNull)
{
	//if (MakeHandNull != NULL) {
		//CollisionComp->DetachFromParent(true);
		CollisionComp->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		CollisionComp->SetSimulatePhysics(true);
		//MakeHandNull = NULL;

		//it is set to QueryAndPhysics so it has Query so you can pick it later
		CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		//so the player can push it around and stand on it
		InteractAbleMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

		Held = false;

		if (isHanded == EHandedEnum::HE_Medium) {
			CollisionComp->SetPhysicsLinearVelocity(FVector(0, 0, 0));
			CollisionComp->SetPhysicsAngularVelocity(FVector(0, 0, 0));
		}
	//}
}

void AInteractSphere::Throw(FVector Direction)
{
	if (!Held)
	CollisionComp->AddForce(Direction);
	//CollisionComp->AddImpulse(Direction);
}

void AInteractSphere::ZeroVelocity()
{
	CollisionComp->SetPhysicsLinearVelocity(FVector(0, 0, 0));
}

void AInteractSphere::DampenVelocity(float DampenBy)
{
	if (GetVelocity().Size() > 1.0f) {
		CollisionComp->SetPhysicsLinearVelocity(FVector(GetVelocity().X / DampenBy, GetVelocity().Y / DampenBy, GetVelocity().Z));
	} 
	//needs to stop intirally
}
