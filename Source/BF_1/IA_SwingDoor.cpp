// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "IA_SwingDoor.h"
#include "Runtime/Engine/Classes/Components/TimelineComponent.h"


// Sets default values  
AIA_SwingDoor::AIA_SwingDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorPivot = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));
	CollisionComp->AttachTo(DoorPivot);
	RootComponent = DoorPivot;

	RotateTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));

	InterpFunction.BindUFunction(this, FName("TimelineVectorReturn"));
	TimelineFinished.BindUFunction(this, FName("OnTimelineFinished"));/**/

	//SetPivotOffset(FVector(0.0f, 100.0f, 0.0f));
	
	//pivot

}

// Called when the game starts or when spawned
void AIA_SwingDoor::BeginPlay()
{
	Super::BeginPlay();

	if (FCurve) {
		//RotateTimeline->AddInterpVector(VCurve, InterpFunction, FName("Alpha"));
		RotateTimeline->AddInterpFloat(FCurve, InterpFunction, FName("Alpha"));
		RotateTimeline->SetTimelineFinishedFunc(TimelineFinished);//OnTimelineFinished);

		RotateTimeline->SetLooping(false);

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "curve");
	}/**/
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, GetPivotOffset().ToString());
}

void AIA_SwingDoor::TimelineVectorReturn(float value)
{
	//SetActorRotation(value.Rotation());
	SetActorRotation(FRotator(0.0f, value, 0.0f));
	//InteractAbleMesh->AddWorldRotation(FQuat(0.0f, value, 0.0f, 1.0f));
	//InteractAbleMesh->RelativeRotation = FRotator(0.0f, value, 0.0f);
	//CollisionComp->SetWorldRotation(FQuat(0.0f, value, 0.0f, 1.0f));
	/**/
}

void AIA_SwingDoor::OnTimelineFinished() 
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Finish");
}/**/

void AIA_SwingDoor::InteractWithPlayer()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "WithPlayer");
	if (RotateTimeline->GetPlaybackPosition() == 0.0f) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Play");
		RotateTimeline->Play();
	}
	else if (RotateTimeline->GetPlaybackPosition() == RotateTimeline->GetTimelineLength()) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Reverse");
		RotateTimeline->Reverse();
	}
}