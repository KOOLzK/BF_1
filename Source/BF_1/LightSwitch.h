// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LightSwitch.generated.h"

UCLASS()
class BF_1_API ALightSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightSwitch();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	class UBoxComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAssess = "true"))
	class UStaticMeshComponent* SwitchMesh;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Text)
	class ATextRenderActor* ButtonPrompt;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Text)
	class UStaticMeshComponent* ButtonPromptMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Text)
	UMaterial* ButtonPrompMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Text)
	UMaterial* SeeThroughMaterial;

	UPROPERTY(EditAnywhere, Category = AI)
	FName LightName;

	/*default state, when level is loaded; 0 = off, 1 = on, 2 = blinking*/
	UPROPERTY(EditAnywhere, Category = Light)
	int stateOne;

	/*second state, after using once; 0 = off, 1 = on, 2 = blinking*/
	UPROPERTY(EditAnywhere, Category = Light)
	int stateTwo;

	bool OnOff;

	int currentState;

	TArray<AActor*> AllLights;

	TArray<AActor*> MyLights;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void Switch();

	
};
