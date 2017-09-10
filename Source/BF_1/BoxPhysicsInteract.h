// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractAble.h"
#include "BoxPhysicsInteract.generated.h"

/**
 * 
 */
UCLASS()
class BF_1_API ABoxPhysicsInteract : public AInteractAble
{
	GENERATED_BODY()
	
public:
	ABoxPhysicsInteract();

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


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Collision)
	class UBoxComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAssess = "true"))
	class UStaticMeshComponent* InteractAbleMesh;

};
