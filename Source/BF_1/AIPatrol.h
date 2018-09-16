// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AIPatrol.generated.h"
//#include "PowerObject.h"

UCLASS()
class BF_1_API AAIPatrol : public ACharacter //, public PowerObject
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

	void AnimationPoses();

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

	UPROPERTY(EditAnywhere, Category = Audio)
	UAudioComponent* propellerAudioComponent;

	/*when enemy is in lastSeen state, this Particle System is suppost to Maker where the enemy last saw the player*/
	UPROPERTY()
	class UParticleSystemComponent* MovingToLocationMaker;

	/*temporary holds Particle System so it can be set MovingToLocationMaker in BeginPlay*/
	UParticleSystem* TempPS;

	/*maybe add a way to change the Particle System from with in the editer*/
	/*UPROPERTY(VisibleAnywhere, Category = Effects)
	FName ParticleSystemRef;*/

	UPROPERTY(EditAnywhere, Category = Effects)
	class UMaterial* FootPrintMaterial;

	/*UPROPERTY(EditAnywhere, Category = Effects)
	float FootPrintLifeSpan = 5.0;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAssess = "true"))
	class UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAssess = "true"))
	class UStaticMeshComponent* Head;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UMaterial* BodyMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UMaterial* HeadMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UMaterial* SeeThroughMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	bool BodyInvisibleInDark;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	bool HeadInvisibleInDark;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	int AnimationNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	bool AnimationToggle;

	bool LightUpdate;

	float Result;

private:

	UFUNCTION()
	void OnPlayerCaught(APawn* Pawn);

};
