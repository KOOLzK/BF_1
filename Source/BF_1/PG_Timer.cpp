// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "PG_Timer.h"
#include "Switch.h"


APG_Timer::APG_Timer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DelayLight = 1.f;

	EditorIcon = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"), true);
	static ConstructorHelpers::FObjectFinder<UTexture2D> PowerTexture(TEXT("Texture2D'/Game/Textures/PowerSymbol.PowerSymbol'"));
	EditorIcon->Sprite = PowerTexture.Object;
	EditorIcon->ScreenSize = 0.0001f;
	EditorIcon->AttachTo(RootComponent);

	PO = new Switch();
}

// Called when the game starts or when spawned
void APG_Timer::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle PGDelay;
	GetWorldTimerManager().SetTimer(PGDelay, this, &APG_Timer::HookingUp, 0.5f, false);
	/*for (int i = 0; HookUp.Num() > i; i++) {
		if (HookUp[i] != NULL) {
			if (HookUp[i]->IsA(APowerGirdHookUp::StaticClass())) {
				APowerGirdHookUp* temp = Cast<APowerGirdHookUp>(HookUp[i]);
				temp->PO->PlugInTo(PO);
			}
		}
	}*/

	GetWorldTimerManager().SetTimer(lightDelay, this, &APG_Timer::toggle, DelayLight, true);
}

// Called every frame
void APG_Timer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APG_Timer::toggle()
{
	PO->Flip();
}