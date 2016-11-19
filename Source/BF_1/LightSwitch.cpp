// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "LightSwitch.h"
#include "PlayerCharacter.h"
#include "Engine/TextRenderActor.h"


// Sets default values
ALightSwitch::ALightSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CoiComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("switch");
	//CollisionComp->OnComponentHit.AddDynamic(this, &ALevelLoader::OnHit);
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ALightSwitch::OnOverlapBegin);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &ALightSwitch::OnOverlapEnd);
	RootComponent = CollisionComp;

	SwitchMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("SwitchMesh"));
	SwitchMesh->AttachTo(RootComponent);
	
	/*ButtonPrompt = CreateDefaultSubobject <ATextRenderActor>(TEXT("ButtonPrompt"));
	ButtonPrompt->AttachToComponent(RootComponent,);*/

	ButtonPromptMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("ButtonPromptMesh"));
	ButtonPromptMesh->AttachTo(RootComponent);

	OnOff = false;
}

// Called when the game starts or when spawned
void ALightSwitch::BeginPlay()
{
	Super::BeginPlay();
	
	ButtonPromptMesh->SetMaterial(0, SeeThroughMaterial);

}

// Called every frame
void ALightSwitch::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ALightSwitch::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself.
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherActor->IsA(APlayerCharacter::StaticClass())) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Hi Player");
			ButtonPromptMesh->SetMaterial(0, ButtonPrompMaterial);
		}
	}
}

void ALightSwitch::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself.
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherActor->IsA(APlayerCharacter::StaticClass())) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Bye Player");
			ButtonPromptMesh->SetMaterial(0, SeeThroughMaterial);
		}
	}
}

void ALightSwitch::Switch()
{
	OnOff = !OnOff;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("Bool: %s"), OnOff ? TEXT("true") : TEXT("false")));
}