// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "LightManager.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"


// Sets default values
ALightManager::ALightManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	//BlackboardComp->AddToRoot();
	//BlackboardComp->InitializeBlackboard(*(BehaviorTree->BlackboardAsset));
	Light = true;
	LightKey = "Light";
	DelayLight = 1.f;
}

// Called when the game starts or when spawned
void ALightManager::BeginPlay()
{
	Super::BeginPlay();
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
}