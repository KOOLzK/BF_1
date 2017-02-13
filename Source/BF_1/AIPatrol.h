// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AIPatrol.generated.h"

UCLASS()
class BF_1_API AAIPatrol : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIPatrol();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual float GetLightingAmount();

	UPROPERTY(EditAnywhere, Category = AI)
	class UBehaviorTree* BehaviorTree;

	/*UPROPERTY(EditAnywhere, Category = AI)
	int numberOfPatrolPoints;*/

	/*UPROPERTY(EditAnywhere, Category = AI)
	FString o;*/

	/*Is used for selecting Patrol Points with the same Name*/
	UPROPERTY(EditAnywhere, Category = AI)
	FName enemyName;

	UPROPERTY(EditAnywhere, Category = AI)
	float MyMaxWalkSpeed;

	/*default is 45.0*/
	UPROPERTY(EditAnywhere, Category = AI)
	float MyMaxStepHeight = 45.0;

	APointLight* PointLight;
	//TArray<AActor*> PatrolPoints;

	UPROPERTY(VisibleAnywhere, Category = AI)
	class UPawnSensingComponent* PawnSensingComp;

	USoundCue* propellerAudioCue;

	UAudioComponent* propellerAudioComponent;

private:

	UFUNCTION()
	void OnPlayerCaught(APawn* Pawn);

};
