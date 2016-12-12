// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "SwingingDoor.h"
#include "PlayerCharacter.h"

// Sets default values
ASwingingDoor::ASwingingDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CoiComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("SwingingDoor");

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ASwingingDoor::OnOverlapBegin);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &ASwingingDoor::OnOverlapEnd);
	RootComponent = CollisionComp;

	HingeComp = CreateDefaultSubobject<USphereComponent>(TEXT("HingeComp"));
	HingeComp->BodyInstance.SetCollisionProfileName("Hinge");
	HingeComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	DoorMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("SwitchMesh"));
	DoorMesh->AttachToComponent(HingeComp, FAttachmentTransformRules::KeepRelativeTransform);


	ButtonPromptMesh1 = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("ButtonPromptMesh1"));
	ButtonPromptMesh1->AttachToComponent(DoorMesh, FAttachmentTransformRules::KeepRelativeTransform);

	ButtonPromptMesh2 = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("ButtonPromptMesh2"));
	ButtonPromptMesh2->AttachToComponent(DoorMesh, FAttachmentTransformRules::KeepRelativeTransform);

	openState = false;

	//SwingDelay = 0.5f;

}

// Called when the game starts or when spawned
void ASwingingDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASwingingDoor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	/*if (openState) 
	{
		if (HingeComp->GetComponentRotation().Yaw < 90.0f)     //>AddLocalRotation()
		{
			HingeComp->AddLocalRotation(FQuat(0, 0, 0.01f, 0));
		}
	}
	else
	{
		if (HingeComp->GetComponentRotation().Yaw > 0.0f)
		{
			HingeComp->AddLocalRotation(FQuat(0, 0, -0.01f, 0));
		}
	}*/

}

void ASwingingDoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself.
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherActor->IsA(APlayerCharacter::StaticClass())) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Hi Player");
			ButtonPromptMesh1->SetMaterial(0, ButtonPrompMaterial);
			ButtonPromptMesh2->SetMaterial(0, ButtonPrompMaterial);
		}
	}
}

void ASwingingDoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself.
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherActor->IsA(APlayerCharacter::StaticClass())) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Bye Player");
			ButtonPromptMesh1->SetMaterial(0, SeeThroughMaterial);
			ButtonPromptMesh2->SetMaterial(0, SeeThroughMaterial);
		}
	}
}

void ASwingingDoor::Use()
{
	openState = !openState;
	GetWorldTimerManager().SetTimer(SwingDelay, this, &ASwingingDoor::Swinging, 0.5f, false);
}

void ASwingingDoor::Swinging()
{
	if (openState)
	{
		if (HingeComp->GetComponentRotation().Yaw < 90.0f)     //>AddLocalRotation()
		{
			HingeComp->SetRelativeRotation(FQuat(HingeComp->RelativeRotation.Roll, HingeComp->RelativeRotation.Pitch, HingeComp->RelativeRotation.Yaw + 1.0f, 0));//>AddLocalRotation(FQuat(0, 0, 1.0f, 0));
			//HingeComp->RelativeRotation.Yaw += 1.f;
			GetWorldTimerManager().SetTimer(SwingDelay, this, &ASwingingDoor::Swinging, 0.5f, false);
		}
	}
	else
	{
		if (HingeComp->GetComponentRotation().Yaw > 0.0f)
		{
			HingeComp->SetRelativeRotation(FQuat(0, 0, -1.0f, 0));
			GetWorldTimerManager().SetTimer(SwingDelay, this, &ASwingingDoor::Swinging, 0.5f, false);
		}
	}
}