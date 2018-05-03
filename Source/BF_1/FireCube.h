// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractCube.h"
#include "FireCube.generated.h"

/**
 * 
 */
UCLASS()
class BF_1_API AFireCube : public AInteractCube
{
	GENERATED_BODY()
	
public:
	AFireCube();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	void WindStrength(FVector Direction);

	void WindGone();

	void SetFireStart(FVector Location);

	FVector WindDirection;

	void Destroyed();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Collision)
	class UBoxComponent* CollisionFireStart;//maybe make pawn
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Collision)
	class UBoxComponent* CollisionFireReach;

	UPROPERTY()
	class UParticleSystemComponent* FirePS;

	/*temporary holds Particle System so it can be set FirePS in BeginPlay*/
	UParticleSystem* TempPS;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Particle)
	bool ChangeAbleAtRunTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Particle)
	float Spawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Particle)
	float LifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Particle)
	FVector InitalVeloctiy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Particle)
	FVector FireStartSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ID)
	bool OnFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ID)
	bool DestroyAble;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ID)
	float DestroyTimer;

	int WarmUp;

	float FireScale;

	float TimeDelay;

	bool OneCal;

	FVector MinsScale;

};
