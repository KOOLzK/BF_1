// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "PG_CardReader.h"
#include <iostream>
#include <sstream>
#include <string>
#include "Switch.h"

//make IA_CardPickUp

APG_CardReader::APG_CardReader() 
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EditorIcon = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"), true);
	static ConstructorHelpers::FObjectFinder<UTexture2D> PowerTexture(TEXT("Texture2D'/Game/Textures/PowerSymbol.PowerSymbol'"));
	EditorIcon->Sprite = PowerTexture.Object;
	EditorIcon->ScreenSize = 0.001f;
	//EditorIcon->AttachTo(CollisionComp);
	EditorIcon->SetupAttachment(CollisionComp);

	LightDisplay = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("LightDisplay"));
	//Head->AttachTo(RootComponent);
	LightDisplay->SetupAttachment(RootComponent);

	

	PO = new Switch();
}
void APG_CardReader::BeginPlay()
{
	Super::BeginPlay();

	/*FOutputDeviceNull ar;
	this->CallFunctionByNameWithArguments(TEXT("StringToInt 10"), ar, NULL, true);*/

	LightDisplay->SetMaterial(0, SwitchMaterial1);

	FTimerHandle PGDelay;
	GetWorldTimerManager().SetTimer(PGDelay, this, &APG_CardReader::HookingUp, 0.5f, false);
}
void APG_CardReader::Tick(float DeltaSeconds)
{

}
void APG_CardReader::InteractWithPlayer()
{
	//open file
	/*FString FileNameA = "level.txt";
	FString SaveTextA;
	FFileHelper::LoadFileToString(SaveTextA, *(FPaths::GameDir() + FileNameA));

	FString SearchName = "KeyLevel";
	//find key card number level
	int PositionNumber = SaveTextA.Find(SearchName);
	//SearchName.Len;
	FString SaveTextB = SaveTextA.Mid(PositionNumber, SearchName.Len());
	//has found it
	if (SaveTextB == SearchName) {
		//check if its high enough
		int PositionNumber2 = SaveTextA.Find(SearchName,ESearchCase::IgnoreCase,ESearchDir::FromStart, PositionNumber);
		FString SaveTextC = SaveTextA.Mid(PositionNumber2, 1);

		FString CustemFunction = "StringToInt " + SaveTextC;
		FOutputDeviceNull ar;
		this->CallFunctionByNameWithArguments(*CustemFunction, ar, NULL, true);

		FString display = "CardLevel " + CardLevel;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, display);

		if (CardLevel >= CardLevelRequired) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Level High Enough");
		}
	}*/

	/* CustemFunction = "StringToInt ";
	FOutputDeviceNull ar;
	this->CallFunctionByNameWithArguments(*CustemFunction, ar, NULL, true);

	FString display = "CardLevel " + CardLevel;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, display);*/

	FOutputDeviceNull ar;
	this->CallFunctionByNameWithArguments(TEXT("StringToInt 10"), ar, NULL, true);

	//don't need?
	/*FString SaveTextB = SaveTextA;// +AddLevelComplete + "=1 "; //SaveTextA;//"box .1.";//
	FString FileNameB = "level.txt";
	FFileHelper::SaveStringToFile(SaveTextB, *(FPaths::GameDir() + FileNameB));*/
	
}

void APG_CardReader::SetCardLevel(int Level)
{
	CardLevel = Level;
}

int APG_CardReader::GetRequiredLevel()
{
	return CardLevelRequired;
}

void APG_CardReader::BPFlipState()
{
	PO->Flip();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "flip");

	if (PO->Toggle) {
		//add SwitchMesh colour change
		LightDisplay->SetMaterial(0, SwitchMaterial1);
	}
	else {
		//add SwitchMesh colour change
		LightDisplay->SetMaterial(0, SwitchMaterial2);
	}
}