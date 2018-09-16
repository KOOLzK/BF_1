// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "MirrorLight.h"



AMirrorLight::AMirrorLight()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StartOn = false;


	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/Effects/P_LightRay.P_LightRay'"));
	TempPS = PS.Object;
	LightPS = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LightPSC"));
	//LightPS->AttachTo(RootComponent);
	LightPS->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMirrorLight::BeginPlay()
{
	Super::BeginPlay();

	ShineLight = StartOn;

	LightPS->SetTemplate(TempPS);
}

// Called every frame
void AMirrorLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ShineLight) {
		//Ray Trace
		HitResult = new FHitResult();
		StartTrace = GetActorLocation();
		ForwardVector = GetActorForwardVector();
		EndTrace = ((ForwardVector * 500) + StartTrace);
		TraceParams = new FCollisionQueryParams();

		if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, EEC_InteractAble, *TraceParams))
		{
			if (HitResult->GetActor()->IsA(AMirrorLight::StaticClass())) {
				//check if ray trace storage is the not the same or NULL as Trace Result
				if (Targeting != Cast<AMirrorLight>(HitResult->GetActor())) {
					//check if ray trace storage is empty
					if (Targeting) {
						Targeting->ShineLight = false;
						Targeting = Cast<AMirrorLight>(HitResult->GetActor());
						Targeting->ShineLight = true;
					}
					else {
						Targeting = Cast<AMirrorLight>(HitResult->GetActor());
						Targeting->ShineLight = true;
					}
				}
			}
		}
		else
		{
			if (Targeting) {
				Targeting->ShineLight = false;
				Targeting = NULL;
			}
		}
		LightPS->SetVectorParameter("Source", StartTrace);
		LightPS->SetVectorParameter("Target", EndTrace);
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(255, 0, 0), false, 0.1f);
	}
}