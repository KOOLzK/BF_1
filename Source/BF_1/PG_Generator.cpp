// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "PG_Generator.h"
#include "Generator.h"

APG_Generator::APG_Generator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EditorIcon = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"), true);
	static ConstructorHelpers::FObjectFinder<UTexture2D> PowerTexture(TEXT("Texture2D'/Game/Textures/PowerSymbol.PowerSymbol'"));
	EditorIcon->Sprite = PowerTexture.Object;
	EditorIcon->ScreenSize = 0.001f;
	//EditorIcon->AttachTo(RootComponent);
	EditorIcon->SetupAttachment(RootComponent);

	PO = new Generator();
}

// Called when the game starts or when spawned
void APG_Generator::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle PGDelay;
	GetWorldTimerManager().SetTimer(PGDelay, this, &APG_Generator::HookingUp, 0.5f, false);

	/*for (int i = 0; HookUp.Num() > i; i++) {
		if (HookUp[i] != NULL) {
			if (HookUp[i]->IsA(APowerGirdHookUp::StaticClass())) {
				APowerGirdHookUp* temp = Cast<APowerGirdHookUp>(HookUp[i]);
				temp->PO->PlugInTo(PO);
			}
		}
	}*/
}

