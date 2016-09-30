// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	InputComponent->BindAxis("LookYaw", this, &APlayerCharacter::LookYaw);
	InputComponent->BindAxis("LookPitch", this, &APlayerCharacter::LookPitch);
	InputComponent->BindAction("Use", IE_Pressed, this, &APlayerCharacter::Use);

}

void APlayerCharacter::MoveForward(float val)
{
	FRotator Rotation(0 ,GetActorRotation().Yaw, 0);
	FVector Forward = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
	AddMovementInput(Forward, val);
}

void APlayerCharacter::MoveRight(float val)
{
	FRotator Rotation(0, GetActorRotation().Yaw, 0);
	FVector Right = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
	AddMovementInput(Right, val);
}

void APlayerCharacter::LookYaw(float val)
{
	AddControllerYawInput(val);
}

void APlayerCharacter::LookPitch(float val)
{
	AddControllerPitchInput(val);
}

void APlayerCharacter::Use()
{
}