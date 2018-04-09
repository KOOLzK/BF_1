// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractCube.h"
#include "PG_PoweredDoor.generated.h"

/**
 * 
 */
UCLASS()
class BF_1_API APG_PoweredDoor : public AInteractCube
{
	GENERATED_BODY()
	
		class UTimelineComponent* RotateTimeline;

public:
	
	APG_PoweredDoor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//virtual void Update() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void InteractWithPlayer() override;

	virtual void InteractWithItem(AInteractAble* Item) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Timeline)
	class UCurveFloat* FCurve;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Collision)
	class USceneComponent* DoorPivot;

	UPROPERTY()
	FRotator StartRotation;

	UPROPERTY()
	FRotator EndRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Timeline)
	float ZOffSet;

	UPROPERTY(EditAnywhere, Category = ID)
	UTexture2D* ReticleDisplayLocked;

	UPROPERTY(EditAnywhere, Category = ID)
	bool Locked;

	UPROPERTY(EditAnywhere, Category = ID)
	bool PoweredLocked;

	bool IsClosed;

	UPROPERTY(EditAnywhere, Category = ID)
	bool DeleteUnlockItem;

	//FOnTimelineVector InterpFunction{};

	FOnTimelineFloat InterpFunction{};

	FOnTimelineEvent TimelineFinished{};

	UFUNCTION()
	void TimelineVectorReturn(float value);

	UFUNCTION()
	void OnTimelineFinished();/**/
	
};
