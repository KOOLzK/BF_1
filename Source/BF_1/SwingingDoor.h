// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SwingingDoor.generated.h"

UCLASS()
class BF_1_API ASwingingDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASwingingDoor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void Use();

	UFUNCTION()
	void Swinging();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	class USphereComponent* HingeComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	class UBoxComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAssess = "true"))
	class UStaticMeshComponent* DoorMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Text)
	class UStaticMeshComponent* ButtonPromptMesh1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Text)
	class UStaticMeshComponent* ButtonPromptMesh2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Text)
	UMaterial* ButtonPrompMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Text)
	UMaterial* SeeThroughMaterial;

	bool openState;

	FTimerHandle SwingDelay;
};
