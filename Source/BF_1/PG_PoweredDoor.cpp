// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "PG_PoweredDoor.h"
#include "Runtime/Engine/Classes/Components/TimelineComponent.h"
#include "PlayerCharacter.h"
#include "FlipGate.h"

// Sets default values  
APG_PoweredDoor::APG_PoweredDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorPivot = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));
	//CollisionComp->AttachTo(DoorPivot);
	CollisionComp->SetupAttachment(DoorPivot);
	RootComponent = DoorPivot;

	RotateTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));

	InterpFunction.BindUFunction(this, FName("TimelineVectorReturn"));
	TimelineFinished.BindUFunction(this, FName("OnTimelineFinished"));/**/

																	  //SetPivotOffset(FVector(0.0f, 100.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<UTexture2D> PS(TEXT("Texture2D'/Game/Textures/lock.lock'"));
	ReticleDisplayLocked = PS.Object;

	//pivot
	ZOffSet = 90;

	Locked = true;
	PoweredLocked = true;
	DeleteUnlockItem = false;

	//PO = new FlipGate();
	PO = new PowerObject();
}

// Called when the game starts or when spawned
void APG_PoweredDoor::BeginPlay()
{
	Super::BeginPlay();

	if (FCurve) {
		//RotateTimeline->AddInterpVector(VCurve, InterpFunction, FName("Alpha"));
		RotateTimeline->AddInterpFloat(FCurve, InterpFunction, FName("Alpha"));
		RotateTimeline->SetTimelineFinishedFunc(TimelineFinished);//OnTimelineFinished);

		RotateTimeline->SetLooping(false);

		StartRotation = GetActorRotation();

		EndRotation = FRotator(StartRotation.Pitch, StartRotation.Yaw - ZOffSet, StartRotation.Roll);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "curve");
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, GetPivotOffset().ToString());
}

void APG_PoweredDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PO->IsOn()) {
		RotateTimeline->Play();
	} else {
		RotateTimeline->Reverse();
	}
}

void APG_PoweredDoor::TimelineVectorReturn(float value)
{
	SetActorRotation(FMath::Lerp(StartRotation, EndRotation, value));
}

void APG_PoweredDoor::OnTimelineFinished()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Finish");
}

void APG_PoweredDoor::InteractWithPlayer()
{
	if (PoweredLocked) {
		if (PO->IsOn()) {
			//locked
			ACharacter* cc = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			APlayerCharacter* temp = Cast<APlayerCharacter>(cc);

			/*get player, replace hand icon with locked icon, wait 2 seconds, set hand icon to
			ReticleDisplayCurrent. maybe add new methed to player class to handle this and store the old one
			so it can be set back after*/
			temp->TemporaryReticle(ReticleDisplayLocked, 2.0f);
		}
		else
		{
			//not locked
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "WithPlayer");
			if (RotateTimeline->GetPlaybackPosition() == 0.0f) {
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Play");
				RotateTimeline->Play();
				//RotateTimeline->
			}
			else if (RotateTimeline->GetPlaybackPosition() == RotateTimeline->GetTimelineLength()) {
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Reverse");
				RotateTimeline->Reverse();
			}
		}
	}
}

void APG_PoweredDoor::InteractWithItem(AInteractAble* Item)
{
	/*if (ItemName == Item->ItemName) {
		Locked = false;
		if (DeleteUnlockItem) {
			Item->DetachFromHand();
			Item->Destroy();
		}
	}*/
	//else play sound?
}


/*void APG_PoweredDoor::Update() 
{
	if (PoweredLocked) {
		if (IsClosed) {
			RotateTimeline->Play();
		} else {
			RotateTimeline->Reverse();
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "PoweredLocked");
	} else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Locked");
		Locked = PO->IsOn();
	}
	
}*/
