// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractCube.h"
#include "IA_Switch.generated.h"

/**
 * 
 */
UCLASS()
class BF_1_API AIA_Switch : public AInteractCube
{
	GENERATED_BODY()
	
public:
	AIA_Switch();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void InteractWithPlayer() override;

	virtual void HookingUp() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UMaterial* SwitchMaterial1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UMaterial* SwitchMaterial2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ID)
	bool StartState;

	USoundCue* propellerAudioCue;

	UAudioComponent* propellerAudioComponent;
};
