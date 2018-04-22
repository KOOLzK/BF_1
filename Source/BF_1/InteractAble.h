// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PowerGirdHookUp.h"
#include "InteractAble.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EHandedEnum : uint8
{
	HE_Small 	UMETA(DisplayName = "Small"),
	HE_Medium	UMETA(DisplayName = "Medium")
};

UCLASS()
class BF_1_API AInteractAble : public APowerGirdHookUp
{
	GENERATED_BODY()
	
public:	

	#define EEC_InteractAble ECollisionChannel::ECC_GameTraceChannel1
	#define EEC_Wind ECollisionChannel::ECC_GameTraceChannel2

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

	virtual void AttachToHand(USceneComponent* Hand);

	virtual void DetachFromHand();

	virtual void UpdateAndDelete();

	virtual void Throw(FVector Direction);

	virtual void ZeroVelocity();

	virtual void DampenVelocity(float DampenBy);

	virtual void InteractWithPlayer();

	virtual void InteractWithItem(AInteractAble* Item);//FName ItemName;

	//virtual void Action();//trigger somehow and override it to do different things

	UPROPERTY(EditAnywhere, Category = ID)
	bool HasPhysics;

	UPROPERTY(EditAnywhere, Category = ID)
	FName ItemName;

	//struct ObjectDefinition

	//enum class Handed {Small, Medium};

	//UPROPERTY(EditAnywhere, Category = ID)
	//Handed isHanded;

	UPROPERTY(EditAnywhere, Category = ID)
	EHandedEnum isHanded;

	/*UPROPERTY(EditAnywhere, Category = ID)
	int HandSize;*/

	/*UPROPERTY(EditAnywhere, Category = ID)
	class UArrowComponent* ForwardArrow;*/

	bool Held;

	/*for when object is attached to another*/
	bool LastFrameOutOfBounds;


	UPROPERTY(EditAnywhere, Category = ID)
	class AActor* Attach;

	UPROPERTY(EditAnywhere, Category = ID)
	float AttachDistence;


	/********ADD
	//string Massege; //to display when the player can't interact

	//Forward Vector so it can be set the the players Forward Vector so small interactables look right 
	while being held and so medium ones can be snap to forward if the player is rotating and presses
	the switch active hand key //don't know if i need this anymore
	*/


	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAssess = "true"))
	//class UStaticMeshComponent* InteractAbleMesh;
	
	//override with box or sphere
	/*UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	class UShapeComponent* CollisionComp;*/
};
