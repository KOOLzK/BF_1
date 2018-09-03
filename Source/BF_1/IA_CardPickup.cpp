// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "IA_CardPickup.h"
#include "PlayerCharacter.h"


AIA_CardPickup::AIA_CardPickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UTexture2D> PS(TEXT("Texture2D'/Game/Textures/Pickup.Pickup'"));
	PickupDisplay = PS.Object;
}
void AIA_CardPickup::BeginPlay()
{
	Super::BeginPlay();
	cc = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

}
void AIA_CardPickup::Tick(float DeltaSeconds)
{
	
}
void AIA_CardPickup::AttachToHand(USceneComponent* Hand)
{
	FOutputDeviceNull ar;
	this->CallFunctionByNameWithArguments(TEXT("PickupCard"), ar, NULL, true);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "interact");
}
void AIA_CardPickup::Focused()
{
	Super::Focused();

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Pickup");

	//ACharacter* cc = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	APlayerCharacter* temp = Cast<APlayerCharacter>(cc);
	temp->TemporaryReticle(PickupDisplay, 0.0f);

	temp->HUDHeight = 250.0f;
	temp->HUDWidth = 250.0f;
}
void AIA_CardPickup::Unfocused()
{
	Super::Unfocused();

	//ACharacter* cc = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	APlayerCharacter* temp = Cast<APlayerCharacter>(cc);
	temp->TemporaryReticle(PickupDisplay, 0.0f);

	temp->ResetHUD();
}
int AIA_CardPickup::GetCardLevel()
{
	return CardLevel;
}