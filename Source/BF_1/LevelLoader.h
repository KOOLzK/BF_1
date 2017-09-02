// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LevelLoader.generated.h"

UCLASS()
class BF_1_API ALevelLoader : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelLoader();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	class UBoxComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAssess = "true"))
	class UStaticMeshComponent* LoaderMesh;

	/*Is used to load the level by name, NOTE entering a name to a level that doesn't exist will cause a crash*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Level)
	FName LevelName;

	UPROPERTY(EditDefaultsOnly, Category = Level)
	FName LevelKey;

	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditAnywhere, Category = Variable)
	class UBehaviorTree* GlobalVariableAccess;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
	void OnOverLapB(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
};

/*
Ref

crap

/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material)
UMaterial* Material;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Level)
ULevel* NameToLoad;*

//UFUNCTION()
//void OnHit(UPrimitiveComponent* HitComp, AActor* Actor, UPrimitiveComponent* Other, FVector Impulse, const FHitResult & Hit);
//void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

// UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult &, SweepResult)

*/