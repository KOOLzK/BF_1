// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InteractAble.generated.h"



UCLASS()
class BF_1_API AInteractAble : public AActor
{
	GENERATED_BODY()
	
public:	

	#define EEC_InteractAble ECollisionChannel::ECC_GameTraceChannel1

	// Sets default values for this actor's properties
	AInteractAble();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//called when the player looks at this actor, makes glowing outline (spell silawet)
	virtual void Focused();

	//called when the player stops looking at this actor, turns off glowing
	virtual void Unfocused();

	virtual void AttachToHead(USceneComponent* Head);

	virtual void DetachFromHead();

	bool HasPhysics;

	UPROPERTY(EditAnywhere, Category = Camera)
	FName ItemName;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAssess = "true"))
	//class UStaticMeshComponent* InteractAbleMesh;
	
	//override with box or sphere
	/*UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	class UShapeComponent* CollisionComp;*/
};
