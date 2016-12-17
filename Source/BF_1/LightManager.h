// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LightManager.generated.h"
//#include "BlueprintType.generated.h"

/*UENUM()
enum class LightState : uint8
{
	On			UMETA(DisplayName = "On"),
	Blink		UMETA(DisplayName = "Blink"),
	Off			UMETA(DisplayName = "Off")
};*/
/*UENUM()
namespace LightState
{
	//256 entries max
	enum Type
	{
		VE_Dance     UMETA(DisplayName = "Dance"),
		VE_Rain         UMETA(DisplayName = "Rain"),
		VE_Song        UMETA(DisplayName = "Song"),

		//~~~

		//256th entry
		VE_Max        UMETA(Hidden),
	};
}*/

UCLASS()
class BF_1_API ALightManager : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Light)
	FName LightKey;

public:
	// Sets default values for this actor's properties
	ALightManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	//UPROPERTY(EditAnywhere, Category = Light)
	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditAnywhere, Category = Light)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, Category = Light)
	float DelayLight;

	FTimerHandle lightDelay;

	void toggle();

	bool Light;

	//enum LightState { Off, On, Blink };

	//LightState currentState;

	//int currentState;

	/*UPROPERTY(EditAnywhere, Category = Light)
	TEnumAsByte<LightState> stateOne;

	UPROPERTY(EditAnywhere, Category = Light)
	TEnumAsByte<LightState> stateTwo;

	UPROPERTY(EditAnywhere, Category = Light)
	int stateOne;

	UPROPERTY(EditAnywhere, Category = Light)
	int stateTwo;*/

};
