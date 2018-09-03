// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractCube.h"
#include "IA_CardPickup.generated.h"

/**
 * 
 */
UCLASS()
class BF_1_API AIA_CardPickup : public AInteractCube
{
	GENERATED_BODY()
	
	AIA_CardPickup();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	//virtual void InteractWithPlayer() override;

	virtual void Focused() override;

	virtual void Unfocused() override;

	virtual void AttachToHand(USceneComponent* Hand) override;
	
	UFUNCTION(BlueprintCallable, Category = ID)
	int GetCardLevel();

	UPROPERTY(EditAnywhere, Category = ID)
	int CardLevel;

	UPROPERTY(EditAnywhere, Category = ID)
	UTexture2D* PickupDisplay;

	ACharacter* cc;
};
