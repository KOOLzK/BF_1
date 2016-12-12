// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "AIPatrol.h"
#include "AIPatrolController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "BlinkingLight.h"


// Sets default values
AAIPatrol::AAIPatrol()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(90.f);

	MyMaxWalkSpeed = 1000;// GetCharacterMovement()->MaxWalkSpeed;

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

	static ConstructorHelpers::FObjectFinder<USoundCue> propellerCue(TEXT("'/Game/Sounds/Church_Ambiance_Cue.Church_Ambiance_Cue'"));//'/Game/Sounds/Cowboy_with_spurs-G-rant_Cue.Cowboy_with_spurs-G-rant_Cue'

	propellerAudioCue = propellerCue.Object;

	propellerAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PropellerAudioComp"));

	propellerAudioComponent->bAutoActivate = false;

	propellerAudioComponent->AttachParent = RootComponent;

	propellerAudioComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

}

// Called when the game starts or when spawned
void AAIPatrol::BeginPlay()
{
	Super::BeginPlay();

	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AAIPatrol::OnPlayerCaught);
	}

	if (propellerAudioCue->IsValidLowLevelFast()) {
		propellerAudioComponent->SetSound(propellerAudioCue);
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
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("angry!"));
		AIController->SetPlayerCaught(Pawn);
	}
}

float AAIPatrol::GetLightingAmount()
{
	FVector Loc = GetActorLocation();
	FCollisionQueryParams Params = FCollisionQueryParams(FName(TEXT("LightTrace")), true, this);
	float Result;
	float AllResult = 0;

	ABlinkingLight* BL = nullptr;

	for (TActorIterator<ABlinkingLight> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->IsA(ABlinkingLight::StaticClass()))
		{
			BL = *ActorItr;
			if (BL)//might need to fix this so it doesn't check every BLight in the level
			{
				UPointLightComponent* LightComp = BL->PointLight;

				if (LightComp)
				{
					if (LightComp->IsVisible())
					{
						FVector End = BL->GetActorLocation();
						float Distance = FVector::Dist(Loc, End);
						float LightRadius = LightComp->AttenuationRadius;
						bool bHit = GetWorld()->LineTraceTestByChannel(Loc, End, ECC_Visibility, Params); //ActorLineTraceSingle(HitResult, Loc, End, ECC_Visibility, Params);// LineTraceTest(

						if (Distance <= LightRadius && !bHit)
						{
							Result = FMath::Pow(FMath::Max(0.0f, 1.0f - (Distance / LightRadius)), (LightComp->LightFalloffExponent + 1)) * (LightRadius * 1.25);
						}
						else
						{
							Result = 0.0f;
						}

						if (Result > 1.0f)
						{
							Result = 1.0f;
						}
					}
					else
					{
						Result = 0.0f;
					}
				}
			}
		}
		if (Result == 1) {
			AllResult = 1;
		}
	}

	/*if (BL)
	{
	UPointLightComponent* LightComp = BL->PointLight;//PointLight->PointLightComponent;

	if (LightComp)
	{
	if (LightComp->IsVisible())
	{
	FVector End = BL->GetActorLocation();
	float Distance = FVector::Dist(Loc, End);
	float LightRadius = LightComp->AttenuationRadius;
	bool bHit = GetWorld()->LineTraceTestByChannel(Loc, End, ECC_Visibility, Params); //ActorLineTraceSingle(HitResult, Loc, End, ECC_Visibility, Params);// LineTraceTest(

	if (Distance <= LightRadius && !bHit)
	{
	//Result = FMath::Pow(1.0 - (Distance / LightRadius), (LightComp->LightFalloffExponent + 1) * (LightRadius * 1.25));
	//Result = FMath::Clamp(Result, 0.0f, 1.0f);

	Result = FMath::Pow(FMath::Max(0.0f, 1.0f - (Distance / LightRadius)), (LightComp->LightFalloffExponent + 1)) * (LightRadius * 1.25);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(Result));// "" + Result);
	}
	else
	{
	Result = 0.0f;
	}

	if (Result > 1.0f)
	{
	Result = 1.0f;
	}
	}
	else
	{
	Result = 0.0f;
	}
	}
	}*/

	/*FString VeryCleanString = FString::SanitizeFloat(Result);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, enemyName.ToString() + VeryCleanString);*/

	return AllResult;
}