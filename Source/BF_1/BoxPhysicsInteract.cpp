// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "BoxPhysicsInteract.h"

// change name to InteractBox 05/01/2018


// Sets default values  
ABoxPhysicsInteract::ABoxPhysicsInteract()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CoiComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("PhysicsInteract");
	CollisionComp->SetCollisionResponseToChannel(EEC_InteractAble, ECollisionResponse::ECR_Block);
	
	HasPhysics = false;
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = CollisionComp;

	InteractAbleMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("InteractAbleMesh"));
	InteractAbleMesh->AttachTo(CollisionComp);

	ZLevelRespone = -10000;

	HandSize = 0;

	AttachDistence = 100;
}

// Called when the game starts or when spawned
void ABoxPhysicsInteract::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
	CollisionComp->SetSimulatePhysics(HasPhysics);

	/*if (HandSize < 1) {
		isHanded = EHandedEnum::HE_Small;
	}
	else {
		isHanded = EHandedEnum::HE_Medium;
	}*/
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

	//all of this was tril and error so i don't know all of what its doing
	if (Attach != NULL) {
		float dis = Attach->GetDistanceTo(this);
		if (Attach->IsA(AInteractAble::StaticClass())) {
			AInteractAble* temp = Cast<AInteractAble>(Attach);

			if (dis > AttachDistence) {

				FVector idk = GetActorLocation() - Attach->GetActorLocation();
				if (temp->Held) {
					ACharacter* cc = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
					//cc->GetCapsuleComponent()->AddForce(idk);
					cc->AddMovementInput(idk, 1.0f);
				} else {
					temp->Throw(idk * (idk.Size() / 2));//times idk?
					temp->LastFrameOutOfBounds = true;
				}

			} else { //if(dis > AttachDistence - 10.0f){
				/*if (temp->LastFrameOutOfBounds) {
					//if (temp->GetVelocity().IsZero()) { //IsNearlyZero()) {
					if (temp->GetVelocity().Size() <= 1.0f) {
						temp->LastFrameOutOfBounds = false;
					} else {
						temp->DampenVelocity(2.0f);
					}
				}*/
				temp->DampenVelocity(1.1f);
				/*FVector idk2 = Attach->GetVelocity();
				FVector idk3(1.0f, 1.0f, 1.0f);

				if(idk2.X > idk3.X || idk2.Y > idk3.Y){
					idk2 /= 2;
				} else {
					//Attach->seta
				}*/
			}
		}
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
	//it is set to PhysicsOnly so it has doesn't have Query so you can't pick it again
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	//so it doesn't push the player around
	InteractAbleMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	CollisionComp->AttachToComponent(Head, FAttachmentTransformRules::KeepWorldTransform);
}

void ABoxPhysicsInteract::DetachFromHead()
{
	CollisionComp->DetachFromParent(true);
	CollisionComp->SetSimulatePhysics(true);
	//it is set to QueryAndPhysics so it has Query so you can pick it later
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//so the player can push it around and stand on it
	InteractAbleMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

	if (isHanded == EHandedEnum::HE_Medium) {
		CollisionComp->SetPhysicsLinearVelocity(FVector(0, 0, 0));
	}
}

void ABoxPhysicsInteract::Throw(FVector Direction)
{
	CollisionComp->AddForce(Direction);
}