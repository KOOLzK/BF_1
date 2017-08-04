// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class BF_1_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	class ALightSwitch* currentSwitch;

	class ASwingingDoor* currentDoor;

	UCameraComponent* PlayerCamera;

	UPROPERTY(EditDefaultsOnly, Category = Level)
	FName LevelKey;

	FName currentLevel;

	UPROPERTY(EditAnywhere, Category = Move)
	float MyMaxWalkSpeed;

	/*default is 45.0*/
	UPROPERTY(EditAnywhere, Category = Move)
	float MyMaxStepHeight;

	class UBlackboardComponent* BlackboardComp;

	//global variable access
	UPROPERTY(EditAnywhere, Category = Variable)
	class UBehaviorTree* GlobalVariableAccess; 

	UPROPERTY(EditAnywhere, Category = Variable)
	float ZLevelRestart;

	UPROPERTY(EditAnywhere, Category = Variable)
	bool DisplayDebugMessages = false;

	/*INPUTS*/
	void MoveForward(float val);
	void MoveRight(float val);
	void LookYaw(float val);
	void LookPitch(float val);
	void Use();
	void ToggleDebugMessages();

	void Death();

	/*OVERRIDES*/
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex

	/*static FORCEINLINE bool Trace(
		UWorld* World,
		AActor* ActorToIgnore,
		const FVector& Start,
		const FVector& End,
		FHitResult& HitOut,
		ECollisionChannel CollisionChannel = ECC_Pawn,
		bool ReturnPhysMat = false
	) {
		if (!World)
		{
			return false;
		}

		FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, ActorToIgnore);
		TraceParams.bTraceComplex = true;
		//TraceParams.bTraceAsyncScene = true;
		TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;

		//Ignore Actors
		TraceParams.AddIgnoredActor(ActorToIgnore);

		//Re-initialize hit info
		HitOut = FHitResult(ForceInit);

		//Trace!
		World->LineTraceSingle(
			HitOut,		//result
			Start,	//start
			End, //end
			CollisionChannel, //collision channel
			TraceParams
		);

		//Hit any Actor?
		return (HitOut.GetActor() != NULL);
	}*/
};
