// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ActorRespone.generated.h"

UCLASS()
class BF_1_API AActorRespone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorRespone();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	FVector StartLocation;

	float ZLevelRespone;

	UPROPERTY(EditAnywhere, Category = ID)
	float ResponeDelay;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAssess = "true"))
	class UShapeComponent* ShapeMesh;
};
