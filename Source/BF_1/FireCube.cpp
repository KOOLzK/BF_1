// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "FireCube.h"



// Sets default values  
AFireCube::AFireCube()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionFireStart = CreateDefaultSubobject<UBoxComponent>(TEXT("FireComp"));
	CollisionFireStart->BodyInstance.SetCollisionProfileName("FireCube");
	CollisionFireStart->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionFireStart->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//CollisionFireStart->AttachTo(RootComponent);
	CollisionFireStart->SetupAttachment(RootComponent);

	

	CollisionFireReach = CreateDefaultSubobject<UBoxComponent>(TEXT("ReachComp"));
	CollisionFireReach->BodyInstance.SetCollisionProfileName("ReachCube");
	CollisionFireReach->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionFireReach->SetCollisionResponseToChannel(EEC_Wind, ECollisionResponse::ECR_Overlap);
	//CollisionFireStart->SetCollisionResponseToChannel(EEC_InteractAble, ECollisionResponse::ECR_Block);
	
	CollisionFireReach->OnComponentBeginOverlap.AddDynamic(this, &AFireCube::OnOverlapBegin);
	CollisionFireReach->OnComponentEndOverlap.AddDynamic(this, &AFireCube::OnOverlapEnd);

	//CollisionFireReach->AttachTo(CollisionFireStart);
	CollisionFireReach->SetupAttachment(CollisionFireStart);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/Effects/P_FireForInteractAble.P_FireForInteractAble'"));
	TempPS = PS.Object;
	FirePS = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FirePSC"));
	//FirePS->AttachTo(CollisionFireStart);
	FirePS->SetupAttachment(CollisionFireStart);

	//OnFire = false;

	//WarmUp = 0;

	TimeDelay = 0;

	OneCal = false;

	DestroyTimer = 5.5f;

}

void AFireCube::BeginPlay()
{
	Super::BeginPlay();
	
	FirePS->SetTemplate(TempPS);
	//FirePS->SetVectorParameter("wind", FVector(100.0f, 0.0f, 0.0f));
	CollisionFireReach->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionFireReach->SetCollisionResponseToChannel(EEC_Wind, ECollisionResponse::ECR_Block);
	CollisionFireReach->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	CollisionFireReach->SetSimulatePhysics(true);
	CollisionFireReach->SetEnableGravity(false);
	FirePS->SetFloatParameter("spawn", Spawn);

	FireScale = 0.1f;
	CollisionFireStart->SetRelativeScale3D(FVector(FireScale, FireScale, FireScale));
	CollisionFireReach->SetRelativeScale3D(FVector(FireScale * 2, FireScale * 2, FireScale * 2));
	
}

void AFireCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeDelay += DeltaTime;

	FVector direction = CollisionFireReach->GetComponentLocation() - CollisionFireStart->GetComponentLocation();
	//times "up" because fire goes up
	FirePS->SetVectorParameter("wind", direction);

	if (ChangeAbleAtRunTime) {
		FirePS->SetFloatParameter("spawn", Spawn);
		FirePS->SetFloatParameter("lifetime", LifeTime);
		FirePS->SetVectorParameter("startveloctiy", InitalVeloctiy);
	}
	
	//if(WarmUp > 5){
	if (OnFire) {
		//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Orange, "On");
		//FirePS->SetFloatParameter("spawn", LifeTime);

		if (!OneCal) {
			MinsScale = CollisionFireStart->RelativeLocation * 0.1f;

			OneCal = true;
		}

		FirePS->Activate();

		if (DestroyAble) {
			FTimerHandle DestroyDelay;
			GetWorldTimerManager().SetTimer(DestroyDelay, this, &AFireCube::Destroyed, DestroyTimer, false);
		}

		if (TimeDelay > 1.0f) {
			if (FireScale < 1.0f) {
				FireScale += 0.1f;
				//if (FireScale < 1.0f) {
					CollisionFireStart->SetRelativeScale3D(FVector(FireScale, FireScale, FireScale));
					CollisionFireReach->SetRelativeScale3D(FVector(FireScale * 2, FireScale * 2, FireScale * 2));

					CollisionFireStart->SetRelativeLocation(CollisionFireStart->RelativeLocation - MinsScale);
				//}
			}
			TimeDelay = 0.0f;
		}
	} else {
		//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Orange, "Off");
		//FirePS->SetFloatParameter("spawn", 1.0f);
		FirePS->Deactivate();
	}
	/*} else {
		WarmUp++;
	}*/

	
		
	
	//float Distance = CollisionFireReach->getdis;
	//FMath::Pow
	//pow();
	
	double distance = sqrt(
	pow(CollisionFireReach->GetComponentLocation().X - CollisionFireStart->GetComponentLocation().X, 2) +
	pow(CollisionFireReach->GetComponentLocation().Y - CollisionFireStart->GetComponentLocation().Y, 2) +
	pow(CollisionFireReach->GetComponentLocation().Z - CollisionFireStart->GetComponentLocation().Z, 2));

	CollisionFireReach->AddForce(InitalVeloctiy * 50);

	//if (CollisionFireReach->RelativeLocation.Size() < 2500){//LifeTime * 40) {
	if (distance > 100) {
		FVector Len = CollisionFireReach->GetComponentVelocity();
		Len;
		CollisionFireReach->AddForce(-direction * direction.Size());
	} else {
		//CollisionFireReach->AddForce(InitalVeloctiy);
		CollisionFireReach->SetPhysicsLinearVelocity(FVector(CollisionFireReach->GetPhysicsLinearVelocity().X / 1.1f, CollisionFireReach->GetPhysicsLinearVelocity().Y / 1.1f, CollisionFireReach->GetPhysicsLinearVelocity().Z / 1.1f));
		//CollisionFireReach->GetPhysicsLinearVelocity().X;
	}


	if (WindDirection.Size() > 1.0f) {
		CollisionFireReach->AddForce(WindDirection);
	}
	//CollisionFireStart->SetRelativeLocation(FVector(sin(DeltaTime) * 10000,0.0f, 0.0f));
	//sin(DeltaTime);
	//CollisionFireStart->SetAllPhysicsLinearVelocity()
	//CollisionFireStart->SetPhysicsLinearVelocity(FVector(10.0f, 0.0f, 0.0f));
}

void AFireCube::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherActor->IsA(AFireCube::StaticClass())) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Begin");
			if (OnFire) {
				AFireCube* temp = Cast<AFireCube>(OtherActor);
				
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, SweepResult.TraceStart.ToString());// SweepResult.ImpactPoint.ToString()
				
				//not my'n 
				TArray<FHitResult> AllResults;

				// Get the location of this actor
				auto Start = GetActorLocation();
				// Get the location of the other component
				auto End = OtherComp->GetComponentLocation();
				// Use a slightly larger radius to ensure we find the same result
				auto CollisionRadius = FVector::Dist(Start, End) * 1.1f;

				// Now do a spherical sweep to find the overlap
				GetWorld()->SweepMultiByObjectType(
					AllResults,
					Start,
					End,
					FQuat::Identity,
					0,
					FCollisionShape::MakeSphere(CollisionRadius),
					FCollisionQueryParams::FCollisionQueryParams(false)
				);

				// Finally check which hit result is the one from this event
				for (auto HitResult : AllResults)
				{
					if (OtherComp->GetUniqueID() == HitResult.GetComponent()->GetUniqueID()) {
						// A component with the same UniqueID means we found our overlap!

						// Do your stuff here, using info from 'HitResult'
						//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, HitResult.Location.ToString());
						//HitResult.Location;
						temp->SetFireStart(HitResult.Location);// -temp->GetActorLocation());
						//if (!OnFire)
						//temp->CollisionFireStart->SetRelativeLocation(HitResult.Location);

						temp->OnFire = true;
					}
				}
			}
		}
	}
	//SweepResult.Location.ToString();
}

void AFireCube::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherActor->IsA(AFireCube::StaticClass())) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "End");
		}
	}

}

void AFireCube::WindStrength(FVector Direction)
{
	WindDirection = Direction;
}

void AFireCube::WindGone()
{
	WindDirection = FVector(0.0f, 0.0f, 0.0f);
}

void AFireCube::SetFireStart(FVector Location) 
{
	if (!OnFire) {
		//CollisionFireStart->SetRelativeLocation(Location);
		CollisionFireStart->SetWorldLocation(Location);
	}
}

void AFireCube::Destroyed()
{
	Destroy();
}