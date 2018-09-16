// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "HidingSpot.h"
#include "PlayerCharacter.h"


// Sets default values
AHidingSpot::AHidingSpot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CoiComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("hidingSpot");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AHidingSpot::OnOverlapBegin);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &AHidingSpot::OnOverlapEnd);
	RootComponent = CollisionComp;

	EditorIcon = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"), true);

	//SpriteTexture = ConstructorStatics.MarkerTextureObject.Get();
	static ConstructorHelpers::FObjectFinder<UTexture2D> SpriteTexture(TEXT("Texture2D'/Engine/EditorMaterials/TargetIcon.TargetIcon'"));
	EditorIcon->Sprite = SpriteTexture.Object;
	//EditorIcon->AttachTo(CollisionComp);
	EditorIcon->SetupAttachment(CollisionComp);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/Effects/Smoke.Smoke'"));
	TempPS = PS.Object;
	Smoke = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SmokePSC"));
	//Smoke->AttachTo(CollisionComp);
	Smoke->SetupAttachment(CollisionComp);
	Smoke->SetRelativeLocation(FVector(0.0f, 0.0f, -0.5f));
}

// Called when the game starts or when spawned
void AHidingSpot::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> StartingActors;
	CollisionComp->GetOverlappingActors(StartingActors);

	for (int i = 0; i < StartingActors.Num(); i++) {
		if (StartingActors[i]->IsA(APlayerCharacter::StaticClass())) {
			APlayerCharacter* temp = Cast<APlayerCharacter>(StartingActors[i]);
			temp->Hidden = true;
		}
	}

	//GetOverlappingActors // https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/GameFramework/AActor/GetOverlappingActors/index.html
	
	Smoke->SetTemplate(TempPS);
}

// Called every frame
void AHidingSpot::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AHidingSpot::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself.
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherActor->IsA(APlayerCharacter::StaticClass())) {
			APlayerCharacter* temp = Cast<APlayerCharacter>(OtherActor);
			temp->Hidden = true;
		}
	}
}

void AHidingSpot::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself.
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherActor->IsA(APlayerCharacter::StaticClass())) {
			APlayerCharacter* temp = Cast<APlayerCharacter>(OtherActor);
			temp->Hidden = false;
		}
	}
}


/*
Ref
https://www.youtube.com/watch?v=YZ3TIqwqOWY
https://wiki.unrealengine.com/Add_in_editor_Icon_to_your_Custom_Actor

crap

*/