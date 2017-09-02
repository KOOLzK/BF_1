// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "EnemyCharacter.h"

//test class //old i don't know if i still need this

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	startLocation = GetActorLocation();
}

// Called every frame
void AEnemyCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FNavLocation NavLoc;
	if (!GetWorld()->GetNavigationSystem()->ProjectPointToNavigation(GetActorLocation(), NavLoc)) {
		SetActorLocation(startLocation);
	}

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

