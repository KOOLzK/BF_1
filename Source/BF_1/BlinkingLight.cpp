// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "BlinkingLight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "PowerObject.h"
//#include "LightSwitch.h"

//light checks the light manager to see if it should be on or off

// Sets default values
ABlinkingLight::ABlinkingLight()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight1"));
	PointLight->Intensity = 3000.f;//DesiredIntensity;
	PointLight->bVisible = true;
	RootComponent = PointLight;

	LightKey = "Light";
	currentState = LightState::Blink;
	currentStateNum = 2;

	PO = new PowerObject();
}

// Called when the game starts or when spawned
void ABlinkingLight::BeginPlay()
{
	Super::BeginPlay();
	//if (BehaviorTree)
	//{
		BlackboardComp->InitializeBlackboard(*(BehaviorTree->BlackboardAsset));
	//}
}

// Called every frame
void ABlinkingLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (BlackboardComp->GetValueAsBool("Light")) {

	}*/


	if (currentStateNum == 0) {
		LightOn = false;
	}
	else if (currentStateNum == 1)
	{
		LightOn = true;
	}
	else if (currentStateNum == 2)
	{
		LightOn = BlackboardComp->GetValueAsBool(LightKey);
	}



	/*if (currentState == LightState::On) {
		LightOn = true;
	}
	else if (currentState == LightState::Blink)
	{
		LightOn = BlackboardComp->GetValueAsBool(LightKey);
	}
	else if (currentState == LightState::Off)
	{
		LightOn = false;
	}*/





	/*if (LightOn)
	{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "true");
	}
	else
	{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "false");
	}*/
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, messege);
	PointLight->SetVisibility(LightOn);
}

