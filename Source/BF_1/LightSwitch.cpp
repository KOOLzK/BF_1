// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "LightSwitch.h"
#include "PlayerCharacter.h"
#include "Engine/TextRenderActor.h"
#include "BlinkingLight.h"
#include "Switch.h"
#include "Generator.h"
/*this may have to be replaced it just turns the light on and off, i can't change the timing in editor
, i can't have two sets of light on different times. i think i should replace it with a power system*/

// Sets default values
ALightSwitch::ALightSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CoiComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("switch");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ALightSwitch::OnOverlapBegin);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &ALightSwitch::OnOverlapEnd);
	RootComponent = CollisionComp;

	SwitchMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("SwitchMesh"));
	SwitchMesh->AttachTo(RootComponent);
	


	ButtonPromptMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("ButtonPromptMesh"));
	ButtonPromptMesh->AttachTo(RootComponent);

	OnOff = true;
	currentState = stateOne;

	static ConstructorHelpers::FObjectFinder<USoundCue> propellerCue(TEXT("'/Game/Sounds/Button_Click_Cue.Button_Click_Cue'"));

	propellerAudioCue = propellerCue.Object;

	propellerAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PropellerAudioComp"));

	propellerAudioComponent->bAutoActivate = false;

	propellerAudioComponent->AttachParent = RootComponent;

	propellerAudioComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

	//Generator* Gen = new Generator();
	S = new Switch();
	//S->PlugInTo(Gen);
}

// Called when the game starts or when spawned
void ALightSwitch::BeginPlay()
{
	Super::BeginPlay();
	
	SwitchMesh->SetMaterial(0, SwitchMaterial1);
	//UMaterial* GlovesMaterialInstanceDynamic = SwitchMesh->CreateAndSetMaterialInstanceDynamic(0);
	ButtonPromptMesh->SetMaterial(0, SeeThroughMaterial);

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABlinkingLight::StaticClass(), AllLights);

	for (int i = 0; i < AllLights.Num(); i++) {
		ABlinkingLight* temp = Cast<ABlinkingLight>(AllLights[i]);
		if (LightName == temp->LightName) {
			MyLights.Add(temp);
			temp->PO->PlugInTo(S);
		}
	}
	
	if (MyLights.Num() > 0) {
		for (int i = 0; i < MyLights.Num(); i++) {
			ABlinkingLight* temp = Cast<ABlinkingLight>(MyLights[i]);
			if (OnOff)
			{

				temp->currentStateNum = stateOne;
			}
			else
			{
				temp->currentStateNum = stateTwo;
			}
		}
	}

	if (propellerAudioCue->IsValidLowLevelFast()) {
		propellerAudioComponent->SetSound(propellerAudioCue);
	}
}

// Called every frame
void ALightSwitch::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ALightSwitch::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself.
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherActor->IsA(APlayerCharacter::StaticClass())) {
			ButtonPromptMesh->SetMaterial(0, ButtonPrompMaterial);
		}
	}
}

void ALightSwitch::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself.
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherActor->IsA(APlayerCharacter::StaticClass())) {
			ButtonPromptMesh->SetMaterial(0, SeeThroughMaterial);
		}
	}
}

void ALightSwitch::Switching()
{
	OnOff = !OnOff;

	propellerAudioComponent->Play();

	S->Flip();
	/*
	if (MyLights.Num() > 0) {
		for (int i = 0; i < MyLights.Num(); i++) {
			ABlinkingLight* temp = Cast<ABlinkingLight>(MyLights[i]);
			if (OnOff)
			{
				temp->currentStateNum = stateOne;
				//add SwitchMesh colour change
				SwitchMesh->SetMaterial(0, SwitchMaterial1);
			}
			else
			{
				temp->currentStateNum = stateTwo;
				//add SwitchMesh colour change
				SwitchMesh->SetMaterial(0, SwitchMaterial2);
			}
		}
	}*/
	
}

/*
Ref

crap

//CollisionComp->OnComponentHit.AddDynamic(this, &ALevelLoader::OnHit);

/*ButtonPrompt = CreateDefaultSubobject <ATextRenderActor>(TEXT("ButtonPrompt"));
ButtonPrompt->AttachToComponent(RootComponent,);*

//ABlinkingLight::LightState::Blink;

//propellerAudioComponent->SetFloatParameter(FName("pitch"), 2500.f);//for runtime

//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Hi Player");

//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Bye Player");

//ABlinkingLight::LightState::Blink;

//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("Bool: %s"), OnOff ? TEXT("true") : TEXT("false")));


*/