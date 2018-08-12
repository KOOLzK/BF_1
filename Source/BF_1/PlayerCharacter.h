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

	//how far the ray trace goes that lets the player pick things up
	UPROPERTY(EditAnywhere, Category = Variable)
	float PlayerReach; 
	//1000 is to far



	/*INPUTS*/
	void MoveForward(float val);
	void MoveRight(float val);
	void LookYaw(float val);
	void LookPitch(float val);
	void Use();
	void ToggleDebugMessages();

	void ActiveHand();
	void EmptyHand();
	void EmptyHandCharge();
	void Use2Down();//rename
	void Use2Up();//rename


	
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

	UFUNCTION(BlueprintPure, Category = HUD)
	UTexture2D* GetCurrentDispay();

	UFUNCTION(BlueprintPure, Category = HUD)
	float GetHUDWidth();

	UFUNCTION(BlueprintPure, Category = HUD)
	float GetHUDHeight();

	UFUNCTION(BlueprintPure, Category = Light)
	UPointLightComponent* GetLight();
	
	UFUNCTION(BlueprintCallable, Category = DeathOfPlayer)
	float DeathLook(float X, float Y, float Z);//FRotator* FoundLook

	/*UFUNCTION(BlueprintCallable, Category = HUD)
	UTexture2D UpdateCurrentDispay();*/

	void ReloadLevel();

	void TemporaryReticle(UTexture2D* Display, float time);

	void ResetReticle();

	UFUNCTION(BlueprintCallable, Category = DeathOfPlayer)
	void PressToDie();


	FTimerHandle ReloadLevelDelay;

	FTimerHandle TemporaryReticleDelay;

	//stores the Interact Able the player is looking at
	class AInteractAble* Targeting;

	/******************i only now noticed these say "head" instead of "hand", this should be changed
	at the same time as InteractAble cause i think its the same. done 12/01/2018*/

	//stores the item the player is holding in the right hand
	class AInteractAble* RightHand;

	//stores the item the player is holding in the left hand
	class AInteractAble* LeftHand;

	//stores the bigger item the player is holding in the both Hands
	class AInteractAble* BothHands;

	//don't think this is going to work, remove?
	//UStaticMeshSocket* RightSocket;

	UPROPERTY(EditAnywhere, Category = Camera)
	class USceneComponent* RightHandOffset;

	UPROPERTY(EditAnywhere, Category = Camera)
	class APhysicsInteract* RightHandOffset2;

	UPROPERTY(EditAnywhere, Category = Camera)
	class USceneComponent* LeftHandOffset;

	float HandOffsetDepthX;

	float HandOffsetThorwX;

	float HandOffsetWidthY;

	float HandOffsetActiveZ;

	float HandOffsetInactiveZ;

	bool IsRightHandActive;

	bool ChargingThrow;

	float ThrowStrength;

	bool Using;

	UPROPERTY(EditAnywhere, Category = HUD)
	UTexture2D* ReticleDisplayTarget;

	UPROPERTY(EditAnywhere, Category = HUD)
	UTexture2D* ReticleDisplayInteract;

	UPROPERTY(EditAnywhere, Category = HUD)
	UTexture2D* ReticleDisplayDeath;

	UPROPERTY(EditAnywhere, Category = HUD)
	UTexture2D* ReticleDisplayCurrent;

	UPROPERTY(EditAnywhere, Category = HUD)
	UTexture2D* ReticleDisplayOld;

	float HUDWidth;

	float HUDHeight;

	UPROPERTY(BlueprintReadOnly, Category = DeathOfPlayer)
	bool dead;

	UPROPERTY(BlueprintReadWrite, Category = DeathOfPlayer)
	FVector DeathTrun;

	FRotator FoundLook;

	UPROPERTY(EditAnywhere, Category = Light)
	class UPointLightComponent* PointLight;

	bool LoadCheckPoint;

	FVector CheckPointVector;

	//AHUD PlayerHUD;

	//class UUserWidget* HUDWidget;


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
