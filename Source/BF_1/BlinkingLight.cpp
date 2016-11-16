// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "BlinkingLight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"


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
}

// Called when the game starts or when spawned
void ABlinkingLight::BeginPlay()
{
	Super::BeginPlay();
	BlackboardComp->InitializeBlackboard(*(BehaviorTree->BlackboardAsset));
}

// Called every frame
void ABlinkingLight::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	/*if (BlackboardComp->GetValueAsBool("Light")) {

	}*/
	bool temp = BlackboardComp->GetValueAsBool(LightKey);
	if (temp)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "true");
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "false");
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, messege);
	PointLight->SetVisibility(temp);
}

