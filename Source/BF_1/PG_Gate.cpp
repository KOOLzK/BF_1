// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "PG_Gate.h"
#include "AndGate.h"
#include "OrGate.h"
#include "NotGate.h"



APG_Gate::APG_Gate()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//GateIsAn = EGateEnum::GE_Or;

	EditorIcon = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"), true);
	static ConstructorHelpers::FObjectFinder<UTexture2D> PowerTexture(TEXT("Texture2D'/Game/Textures/PowerSymbol.PowerSymbol'"));
	EditorIcon->Sprite = PowerTexture.Object;
	EditorIcon->ScreenSize = 0.001f;
	EditorIcon->AttachTo(RootComponent);
	

	//DisplayingArrows();
}

// Called when the game starts or when spawned
void APG_Gate::BeginPlay()
{
	Super::BeginPlay();

	//HookingUp();

	if (GateIsAn == EGateEnum::GE_And) {
		PO = new AndGate();
	}
	else if (GateIsAn == EGateEnum::GE_Or) {
		PO = new OrGate();
	}
	else if (GateIsAn == EGateEnum::GE_Not) {
		PO = new NotGate();
	}

	FTimerHandle PGDelay;
	GetWorldTimerManager().SetTimer(PGDelay, this, &APG_Gate::HookingUp, 0.5f, false);

	/*for (int i = 0; HookUp.Num() > i; i++) {
		if (HookUp[i] != NULL) {
			if (HookUp[i]->IsA(APowerGirdHookUp::StaticClass())) {
				APowerGirdHookUp* temp = Cast<APowerGirdHookUp>(HookUp[i]);
				temp->PO->PlugInTo(PO);
			}
		}
	}*/
}