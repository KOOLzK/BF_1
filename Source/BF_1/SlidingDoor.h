// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SlidingDoor.generated.h"

UCLASS()
class BF_1_API ASlidingDoor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Light)
	FName LightKey;

	float DY;
	
public:	
	// Sets default values for this actor's properties
	ASlidingDoor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/*//for swinging door wops
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	class USphereComponent* HingeComp;*/

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	class UBoxComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAssess = "true"))
	class UStaticMeshComponent* DoorMesh;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	class UStaticMeshComponent* ClosedPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	class UStaticMeshComponent* OpenedPosition;*/
	
	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditAnywhere, Category = Light)
	class UBehaviorTree* BehaviorTree;
	
	UPROPERTY(EditAnywhere, Category = Action)
	float speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Action)
	float ClosedY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Action)
	float OpenedY;

	/*Don't add a Mesh to this, it only exists to have a position to stop. feel free to move in blue print*/
};
