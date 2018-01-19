// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "IA_Switch.h"
#include "Switch.h"


// Sets default values  
AIA_Switch::AIA_Switch()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USoundCue> propellerCue(TEXT("'/Game/Sounds/Button_Click_Cue.Button_Click_Cue'"));

	propellerAudioCue = propellerCue.Object;

	propellerAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PropellerAudioComp"));

	propellerAudioComponent->bAutoActivate = false;

	propellerAudioComponent->AttachParent = RootComponent;

	EditorIcon = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"), true);
	static ConstructorHelpers::FObjectFinder<UTexture2D> PowerTexture(TEXT("Texture2D'/Game/Textures/PowerSymbol.PowerSymbol'"));
	EditorIcon->Sprite = PowerTexture.Object;
	EditorIcon->ScreenSize = 0.001f;
	EditorIcon->AttachTo(CollisionComp);


	PO = new Switch();
}

// Called when the game starts or when spawned
void AIA_Switch::BeginPlay()
{
	Super::BeginPlay();

	InteractAbleMesh->SetMaterial(0, SwitchMaterial1);

	FTimerHandle PGDelay;
	GetWorldTimerManager().SetTimer(PGDelay, this, &AIA_Switch::HookingUp, 0.5f, false);

	/*for (int i = 0; HookUp.Num() > i; i++) {
		if (HookUp[i] != NULL) {
			if (HookUp[i]->IsA(APowerGirdHookUp::StaticClass())) {
				APowerGirdHookUp* temp = Cast<APowerGirdHookUp>(HookUp[i]);
				temp->PO->PlugInTo(PO);
			}
		}
	}*/

	if (propellerAudioCue->IsValidLowLevelFast()) {
		propellerAudioComponent->SetSound(propellerAudioCue);
	}
}

// Called every frame
void AIA_Switch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIA_Switch::InteractWithPlayer()
{
	propellerAudioComponent->Play();

	PO->Flip();

	if (PO->Toggle) {
		//add SwitchMesh colour change
		InteractAbleMesh->SetMaterial(0, SwitchMaterial1);
	} else {
		//add SwitchMesh colour change
		InteractAbleMesh->SetMaterial(0, SwitchMaterial2);
	}
}