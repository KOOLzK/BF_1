// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractCube.h"
#include "FanCube.generated.h"

/**
 * 
 */
UCLASS()
class BF_1_API AFanCube : public AInteractCube
{
	GENERATED_BODY()
	
public:
	AFanCube();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAssess = "true"))
	class UStaticMeshComponent* ConeMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Collision)
	class USphereComponent* WindComp;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	class AFireCube* Fanning;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Particle)
	int FanPower;
};
