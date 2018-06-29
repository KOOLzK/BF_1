// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PowerGirdHookUp.h"
#include "BlinkingLight.generated.h"

UCLASS()//ClassGroup = Custom, meta = (BlueprintSpawnableComponent))
class BF_1_API ABlinkingLight : public APowerGirdHookUp
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Light)
	FName LightKey;

	FName messege;

	bool LightOn;

public:
	// Sets default values for this actor's properties
	ABlinkingLight();// PG_Subject *mod, bool div) : APG_Observer(mod, div);

	enum LightState { On, Blink, Off };

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, Category = "Switch Components")
	class UPointLightComponent* PointLight;

	//UPROPERTY(EditAnywhere, Category = Light)
	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditAnywhere, Category = Light)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, Category = AI)
	FName LightName;

	/*UPROPERTY(EditAnywhere, Category = Light)
	class ALightSwitch* LightSwitch;*/

	LightState currentState;

	int currentStateNum;

	//class PowerObject* PO;

	virtual void Update() override;

	UPROPERTY(EditAnywhere, Category = Navigation)
	class UNavModifierComponent* NavMod;

	/*UPROPERTY(EditAnywhere, Category = Navigation)
	class ANavModifierVolume* Nav;*///this crashes unreal

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Navigation)
	class USphereComponent* NavSphere;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Navigation)
	class ABrush* BRR; *///this crashes unreal

	UPROPERTY(EditAnywhere, Category = Collision)
	UBillboardComponent* EditorIcon2;

	/*UPROPERTY(VisibleAnywhere)
	UBillboardComponent* EditorIcon;

	UPROPERTY(VisibleAnywhere)
	UTexture2D* PowerTexture;*/

	UPROPERTY(EditAnywhere, Category = Collision)
	UTexture2D* PowerTexture2;
};
