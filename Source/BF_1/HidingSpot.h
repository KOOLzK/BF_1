// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HidingSpot.generated.h"

UCLASS()
class BF_1_API AHidingSpot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHidingSpot();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	class UBoxComponent* CollisionComp;

	/*if true Particle System is on*/
	UPROPERTY(EditAnywhere, Category = Collision)
	bool ParticlesOn;

	/*To show the player where they can hide*/
	UPROPERTY()
	class UParticleSystemComponent* Smoke;

	/*temporary holds Particle System so it can be set MovingToLocationMaker in BeginPlay*/
	UParticleSystem* TempPS;


	UPROPERTY(EditAnywhere, Category = Collision)
	UBillboardComponent* EditorIcon;

	UPROPERTY(EditAnywhere, Category = Collision)
	UTexture2D* SpriteTexture;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
};
