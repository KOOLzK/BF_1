// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractAble.h"
#include "PhysicsInteract.generated.h"

/**
 * 
 */
UCLASS()
class BF_1_API APhysicsInteract : public AInteractAble
{
	GENERATED_BODY()

public:
	APhysicsInteract();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	//called when the player looks at this actor, makes glowing outline (spell silawet)
	virtual void Focused() override;

	//called when the player stops looking at this actor, turns off glowing
	virtual void Unfocused() override;


	virtual void AttachToHead(USceneComponent* Head) override;

	virtual void DetachFromHead() override;
	//void AttachHead2(USceneComponent* Head);


	virtual void Throw(FVector Direction) override;

	virtual void ZeroVelocity() override;

	virtual void DampenVelocity(float DampenBy) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Collision)
	class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAssess = "true"))
	class UStaticMeshComponent* InteractAbleMesh;
	
	FVector StartLocation;

	float ZLevelRespone;
};
