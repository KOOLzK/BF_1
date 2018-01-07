// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "BlinkingLight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "PowerObject.h"
//#include "LightSwitch.h"
//#include "AI/Navigation/RecastNavMesh.h"
#include "AI/Navigation/NavModifierVolume.h"
//#include "NavModifierVolume.generated.h"
//#include "C:\Program Files (x86)\Epic Games\4.12\Engine\Source\Runtime\Engine\Classes\AI\Navigation\NavModifierComponent.h"
#include "AI/Navigation/NavModifierComponent.h"
#include "AI/Navigation/NavAreas/NavArea_Default.h"
#include "AI/Navigation/NavAreas/NavArea_Null.h"

//light checks the light manager to see if it should be on or off

// Sets default values
ABlinkingLight::ABlinkingLight()//PG_Subject *mod, bool div)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;//UNavModifierComponent
	//NavModifierComponent
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight1"));
	PointLight->Intensity = 3000.f;//DesiredIntensity;
	PointLight->bVisible = true;
	RootComponent = PointLight;

	LightKey = "Light";
	currentState = LightState::Blink;
	currentStateNum = 2;

	//LightName = " ";

	PO = new PowerObject();
	Observer(PO, PO->IsOn());
	//PO->AttachLight(this);

	NavSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CoiComp"));
	NavSphere->BodyInstance.SetCollisionProfileName("NavigationSphere");
	NavSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	NavSphere->AreaClass = UNavArea_Null::StaticClass();
	NavSphere->SetCanEverAffectNavigation(true); //Set Can Affect Navigation Generation
	
	//NavSphere->SetPhysicsVolume()

	NavMod = CreateDefaultSubobject<UNavModifierComponent>(TEXT("NavModifier"));
	//NavMod->
	//NavSphere->AttachChildren.Add(NavMod);
	//NavMod->AreaClass = UNavArea_Null::StaticClass();//BrushType
	//NavMod->BrushType();

	//BRR = CreateDefaultSubobject<ABrush>(TEXT("BRR"));
	/*BRR->BrushType = EBrushType::Brush_Add;*/

	//NavMod->CalcBounds();
	//NavMod->

	//Nav = new UNavModifierComponent();
	//Nav = CreateDefaultSubobject<ANavModifierVolume>(TEXT("NavModifier"));//<<jeff look at this line
	//Nav->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	//Nav->BrushComponent->set
	//Nav->SetAreaClass(UNavArea::)
	//Nav = CreateDefaultSubobject<UNavModifierComponent>(TEXT("NavModifier"));
	//Nav->AddToRoot();//ComponentBounds
	//Nav->SetAreaClass(UNavArea_Default::StaticClass());
	//Nav->GetNavigationBounds();
	//Nav->setnav
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

	/*
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
*/


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
	//PointLight->SetVisibility(LightOn);
	if (PO->IsOn()) {
		NavSphere->AreaClass = UNavArea_Null::StaticClass();
	}
	else {
		NavSphere->AreaClass = UNavArea_Default::StaticClass();
	}
}

void ABlinkingLight::Update()
{
	//this->CallFunction();
	PointLight->SetVisibility(PO->GetVal());
	//getSubject()->getVal()
	//PO->GetVal();
}