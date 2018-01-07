// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "AIPatrol.h"
#include "PlayerCharacter.h"
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

	//GetCharacterMovement()->MaxStepHeight = MyMaxStepHeight;

	static ConstructorHelpers::FObjectFinder<USoundCue> propellerCue(TEXT("'/Game/Sounds/Church_Ambiance_Cue.Church_Ambiance_Cue'"));//'/Game/Sounds/Cowboy_with_spurs-G-rant_Cue.Cowboy_with_spurs-G-rant_Cue'

	propellerAudioCue = propellerCue.Object;

	propellerAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PropellerAudioComp"));

	propellerAudioComponent->bAutoActivate = false;

	propellerAudioComponent->AttachParent = RootComponent;

	propellerAudioComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/Effects/P_Moving_Spin_Untyped_00.P_Moving_Spin_Untyped_00'"));
	TempPS = PS.Object;
	MovingToLocationMaker = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EnemyMakerPSC"));
	
	Body = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("BodyMesh"));
	Body->AttachTo(RootComponent);

	Head = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("HeadMesh"));
	Head->AttachTo(RootComponent);

	/*maybe get the Material that is set to the mesh so i and other don't have to set BodyMaterial
	and HeadMaterial to get it to work, and so other don't get confused on why setting the mesh 
	material directly does nothing*/
	
	AnimationNumber = 4;
	AnimationToggle = false;
}

// Called when the game starts or when spawned
void AAIPatrol::BeginPlay()
{
	Super::BeginPlay();

	Body->SetMaterial(0, BodyMaterial);
	Head->SetMaterial(0, HeadMaterial);

	GetCharacterMovement()->MaxStepHeight = MyMaxStepHeight;

	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AAIPatrol::OnPlayerCaught);
	}

	if (propellerAudioCue->IsValidLowLevelFast()) {
		propellerAudioComponent->SetSound(propellerAudioCue);
	}

	/*if the Particle System(MovingToLocationMaker) is set in the constructor then the blueprint gets 
	all weird. the camera zooms really far back and is a pain to zoom in again so I'm doing it here 
	in BeginPlay*/
	MovingToLocationMaker->SetTemplate(TempPS);

}

// Called to bind functionality to input
void AAIPatrol::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AAIPatrol::OnPlayerCaught(APawn* Pawn)
{
	APlayerCharacter* temp = Cast<APlayerCharacter>(Pawn);

	if (!temp->Hidden) {

		AAIPatrolController* AIController = Cast<AAIPatrolController>(GetController());
		if (AIController)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("angry!"));
			AIController->SetPlayerCaught(Pawn);
		}
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

	return AllResult;
}

void AAIPatrol::AnimationPoses() 
{
	if (LightUpdate) {
		AnimationToggle = !AnimationToggle;
		LightUpdate = false;
	}

	AAIPatrolController* AIController = Cast<AAIPatrolController>(GetController());
	if (AIController)
	{
		//override AnimationNumber to floating if the AI is stock if(floating){AnimationNumber = 3;}else
		
		if (AIController->CurrentState == AAIPatrolController::State::patrol) {
			AnimationNumber = 0;
		}
		else if (AIController->CurrentState == AAIPatrolController::State::spotted) {
			AnimationNumber = 1;
		}
	}
}

/*
Ref
https://answers.unrealengine.com/questions/253934/how-to-correctly-initialize-decal-components-and-m.html
https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/Components/UDecalComponent/index.html
https://answers.unrealengine.com/questions/67701/how-to-correctly-spawn-a-bullet-hole.html
https://answers.unrealengine.com/questions/198712/how-to-spawn-decal-on-collision.html
https://answers.unrealengine.com/questions/198712/how-to-spawn-decal-on-collision.html
https://answers.unrealengine.com/questions/125678/best-way-to-highlight-under-selected-unit.html#answer-126922



crap

//MovingToLocationMaker->ActivateSystem(true);
//MovingToLocationMaker->SetWorldLocation(FVector(0, 0, 0));
//MovingToLocationMaker->SpawnEvents.
//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MovingToLocationMaker->Template, FVector(0, 0, 0));






/*UPROPERTY(VisibleAnywhere, Category = AI)
UBillboardComponent* temp3 = CreateDefaultSubobject<UBillboardComponent>(TEXT("TargetPoint"));
temp3->AttachTo(RootComponent);* /

//AActor* temp2 = CreateDefaultSubobject<AActor>(TEXT("TargetPoint"));
//temp2->AttachToActor(RootComponent);

/*ATargetPoint* temp = CreateDefaultSubobject<ATargetPoint>(TEXT("TargetPoint"));
temp->AddToRoot();* /



//ATargetPoint* temp;
//temp->AttachRootComponentTo(RootComponent);
//>AttachTo(RootComponent);
//temp->AttachTo();
//RootComponent r = GetRootComponent();

//GetCapsuleComponent()->AttachChildren(temp);
//RootComponent->AttachTo()
//temp->AttachToComponent(GetRootComponent(),);
//PatrolPoints.Add();




//MovingToLocationMaker->SetTemplate(PS.Object);
//MovingToLocationMaker->DeactivateSystem();
//MovingToLocationMaker->AttachParent = propellerAudioComponent;






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
GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, enemyName.ToString() + VeryCleanString);* /

*/