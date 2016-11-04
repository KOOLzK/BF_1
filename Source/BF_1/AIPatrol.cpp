// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "AIPatrol.h"
#include "AIPatrolController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"


// Sets default values
AAIPatrol::AAIPatrol()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(90.f);

	/*UPROPERTY(VisibleAnywhere, Category = AI)
	UBillboardComponent* temp3 = CreateDefaultSubobject<UBillboardComponent>(TEXT("TargetPoint"));
	temp3->AttachTo(RootComponent);*/

	//AActor* temp2 = CreateDefaultSubobject<AActor>(TEXT("TargetPoint"));
	//temp2->AttachToActor(RootComponent);

	/*ATargetPoint* temp = CreateDefaultSubobject<ATargetPoint>(TEXT("TargetPoint"));
	temp->AddToRoot();*/

	

	//ATargetPoint* temp;
	//temp->AttachRootComponentTo(RootComponent);
	//>AttachTo(RootComponent);
	//temp->AttachTo();
	//RootComponent r = GetRootComponent();

	//GetCapsuleComponent()->AttachChildren(temp);
	//RootComponent->AttachTo()
	//temp->AttachToComponent(GetRootComponent(),);
	//PatrolPoints.Add();

}

// Called when the game starts or when spawned
void AAIPatrol::BeginPlay()
{
	Super::BeginPlay();
	
	if (PawnSensingComp) 
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AAIPatrol::OnPlayerCaught);
	}
}

// Called to bind functionality to input
void AAIPatrol::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AAIPatrol::OnPlayerCaught(APawn* Pawn) 
{

	AAIPatrolController* AIController = Cast<AAIPatrolController>(GetController());

	if (AIController) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You have been caught!"));
		AIController->SetPlayerCaught(Pawn);
	}
}

