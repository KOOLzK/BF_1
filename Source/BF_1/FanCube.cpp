// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "FanCube.h"
#include "FireCube.h"


// Sets default values  
AFanCube::AFanCube()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*ConeMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("ConeMesh"));
	ConeMesh->AttachTo(CollisionComp);
	ConeMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ConeMesh->SetCollisionResponseToChannel(EEC_Wind, ECollisionResponse::ECR_Block);*/
	
	WindComp = CreateDefaultSubobject<USphereComponent>(TEXT("WindComp"));
	WindComp->BodyInstance.SetCollisionProfileName("FanCube");
	WindComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	//WindComp->SetCollisionResponseToChannel(EEC_Wind, ECollisionResponse::ECR_Overlap);
	WindComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	WindComp->OnComponentBeginOverlap.AddDynamic(this, &AFanCube::OnOverlapBegin);
	WindComp->OnComponentEndOverlap.AddDynamic(this, &AFanCube::OnOverlapEnd);
	//WindComp->AttachTo(CollisionComp);
	WindComp->SetupAttachment(CollisionComp);

	FanPower = 2;
}

void AFanCube::BeginPlay()
{
	Super::BeginPlay();

	/*ConeMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ConeMesh->SetSimulatePhysics(false);
	ConeMesh->SetEnableGravity(false);*/
}

void AFanCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Fanning != NULL) {
		FVector direction = GetActorLocation() - Fanning->GetActorLocation();
		//Fanning->CollisionFireReach->AddForce(direction);
		Fanning->WindStrength(-direction * direction.Size() * FanPower);
	}
	
}

void AFanCube::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Begin");
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherActor->IsA(AFireCube::StaticClass())) {
			Fanning = Cast<AFireCube>(OtherActor);
			/*FVector direction = GetActorLocation() - Fanning->GetActorLocation();
			//GetDistanceTo(temp);
			Fanning->CollisionFireReach->AddForce(direction);*/
		}
	}
}

void AFanCube::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "End");
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherActor->IsA(AFireCube::StaticClass())) {
			if (Fanning != NULL) {
				Fanning->WindGone();
				Fanning = NULL;
			}
		}
	}
}