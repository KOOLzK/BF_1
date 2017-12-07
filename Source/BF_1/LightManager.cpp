// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "LightManager.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BlinkingLight.h"
#include "LightSwitch.h"

#include "Switch.h"
#include "Generator.h"

/*this may have to be replaced it just turns the light on and off, i can't change the timing in editor
, i can't have two sets of light on different times. i think i should replace it with a power system*/

// Sets default values
ALightManager::ALightManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	Light = true;
	LightKey = "Light";
	DelayLight = 1.f;

	Gen = new Generator();
	Sw = new Switch();
	Sw->PlugInTo(Gen);

}

// Called when the game starts or when spawned
void ALightManager::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABlinkingLight::StaticClass(), AllLights);

	for (int i = 0; i < AllLights.Num(); i++) {
		ABlinkingLight* temp = Cast<ABlinkingLight>(AllLights[i]);
		if (temp->LightName == "none") {
			MyLights.Add(temp);
			temp->PO->PlugInTo(Sw);
		}
	}

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALightSwitch::StaticClass(), AllSwitches);

	for (int i = 0; i < AllSwitches.Num(); i++) {
		ALightSwitch* temp = Cast<ALightSwitch>(AllSwitches[i]);
			MySwitches.Add(temp);
			temp->S->PlugInTo(Sw);
		
	}


	BlackboardComp->InitializeBlackboard(*(BehaviorTree->BlackboardAsset));
	GetWorldTimerManager().SetTimer(lightDelay, this, &ALightManager::toggle, DelayLight, true);

}

// Called every frame
void ALightManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALightManager::toggle()
{
	Light = !Light;
	BlackboardComp->SetValueAsBool(LightKey, Light);

	Sw->Flip();
}

/*
Ref

crap

//BlackboardComp->AddToRoot();
//BlackboardComp->InitializeBlackboard(*(BehaviorTree->BlackboardAsset));

//if (BehaviorTree)
//{
//}

/*if (Light)
{
currentState = stateOne;
}
else
{
currentState = stateTwo;
}*

*/