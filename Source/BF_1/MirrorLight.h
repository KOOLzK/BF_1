// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractCube.h"
#include "MirrorLight.generated.h"

/**
 * 
 */
UCLASS()
class BF_1_API AMirrorLight : public AInteractCube
{
	GENERATED_BODY()
	
public:
	AMirrorLight();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere, Category = Variable)
	bool StartOn;

	bool ShineLight;

	//stores the Interact Able the mirror is looking at
	class AMirrorLight* Targeting;
	
	/*Ray Trace*/
	FHitResult* HitResult;
	FVector StartTrace;
	FVector ForwardVector;
	FVector EndTrace;
	FCollisionQueryParams* TraceParams;



	UPROPERTY()
	class UParticleSystemComponent* LightPS;

	/*temporary holds Particle System so it can be set FirePS in BeginPlay*/
	UParticleSystem* TempPS;
};
