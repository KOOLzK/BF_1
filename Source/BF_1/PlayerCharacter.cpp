// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "PlayerCharacter.h"
#include "LightSwitch.h"
#include "SwingingDoor.h"
#include "AIPatrol.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//this->on

	UCapsuleComponent*  CapsuleComponent = GetCapsuleComponent(); 
	//GetCapsuleComponent()->bGenerateOverlapEvents = true;
	//GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	GetCapsuleComponent()->BodyInstance.SetCollisionProfileName("Player");
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapBegin);//->OnComponentBeginOverlap(this, APlayerCharacter::BeginPlay());
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapEnd);

	currentSwitch = nullptr;

	//back up in case it isn't set
	currentLevel = "puzzle1";

	LevelKey = "CurrentLevel";

	MyMaxWalkSpeed = 500;
	GetCharacterMovement()->MaxWalkSpeed = MyMaxWalkSpeed;

	ZLevelRestart = -10000;
	//BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}


// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	/*if (GlobalVariableAccess)
	{
		BlackboardComp->InitializeBlackboard(*(GlobalVariableAccess->BlackboardAsset));
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "NO");
	}*/
}

// Called every frame
void APlayerCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (GetActorLocation().Z < ZLevelRestart)
	{
		Death();
	}

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
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "E");
	if (currentSwitch != nullptr)
	{
		currentSwitch->Switch();
	}

	if (currentDoor != nullptr)
	{
		currentDoor->Use();
	}
}

void APlayerCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	// Other Actor is the actor that triggered the event. Check that is not ourself.
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherActor->IsA(ALightSwitch::StaticClass())) {
			ALightSwitch* temp = Cast<ALightSwitch>(OtherActor);
			currentSwitch = temp;
		}

		if (OtherActor->IsA(ASwingingDoor::StaticClass())) {
			ASwingingDoor* temp = Cast<ASwingingDoor>(OtherActor);
			currentDoor = temp;
		}

		if (OtherActor->IsA(AAIPatrol::StaticClass())) {
			Death();
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Dead");
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Begin");
}

void APlayerCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself.
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherActor->IsA(ALightSwitch::StaticClass())) {
			currentSwitch = nullptr;
		}

		if (OtherActor->IsA(ASwingingDoor::StaticClass())) {
			currentDoor = nullptr;
		}

	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "End");
	
}

void APlayerCharacter::Death()
{
	//currentLevel = BlackboardComp->GetValueAsName(LevelKey);//GetValueAsBool(LevelKey);
	//UGameplayStatics::OpenLevel(this, currentLevel);
	FString a = UGameplayStatics::GetCurrentLevelName(this);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, a);
	UGameplayStatics::OpenLevel(this, FName(*a));
}