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

	UPROPERTY(EditAnywhere, Category = Camera)
	UCameraComponent* PlayerCamera;

	//old i don't know if i still need this
	UPROPERTY(EditDefaultsOnly, Category = Level)
	FName LevelKey;

	FName currentLevel;

	UPROPERTY(EditAnywhere, Category = Move)
	float MyMaxWalkSpeed;

	/*default is 45.0*/ //player charactor and enemy charactor have trouble with stares, i uses ramps
	UPROPERTY(EditAnywhere, Category = Move)
	float MyMaxStepHeight;

	//old i don't know if i still need this
	class UBlackboardComponent* BlackboardComp;

	//global variable access //old i don't know if i still need this
	UPROPERTY(EditAnywhere, Category = Variable)
	class UBehaviorTree* GlobalVariableAccess; 

	//in case the player falls through or off the map
	UPROPERTY(EditAnywhere, Category = Variable)
	float ZLevelRestart;

	UPROPERTY(EditAnywhere, Category = Variable)
	bool DisplayDebugMessages = false;

	bool Hidden;


	/*Ray Trace*/
	FHitResult* HitResult;
	FVector StartTrace;
	FVector ForwardVector;
	FVector EndTrace;
	FCollisionQueryParams* TraceParams;


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

	//stores the Interact Able the player is looking at
	class AInteractAble* Targeting;

	//stores the item the player is holding in the left head
	class AInteractAble* LeftHead;

	//stores the item the player is holding in the right head
	class AInteractAble* RightHead;

	//don't think this is going to work, remove?
	//UStaticMeshSocket* RightSocket;

	UPROPERTY(EditAnywhere, Category = Camera)
	class USceneComponent* RightHeadOffset;

	UPROPERTY(EditAnywhere, Category = Camera)
	class APhysicsInteract* RightHeadOffset2;
	

	UPROPERTY(EditAnywhere, Category = Camera)
	class USceneComponent* LeftHeadOffset;

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
