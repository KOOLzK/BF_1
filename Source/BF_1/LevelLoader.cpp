// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "LevelLoader.h"
#include "PlayerCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

// Sets default values
ALevelLoader::ALevelLoader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CoiComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("enemy");
	//CollisionComp->OnComponentHit.AddDynamic(this, &ALevelLoader::OnHit);
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ALevelLoader::OnOverLapB);
	RootComponent = CollisionComp;

	LoaderMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("LoaderMesh"));
	LoaderMesh->AttachTo(RootComponent);

	//Material->BlendMode = BLEND_Translucent;
	//Material->Opacity.Constant = 0.5f;
	//LoaderMesh->SetMaterial(0 ,Material);

	LevelKey = "CurrentLevel";

	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}

// Called when the game starts or when spawned
void ALevelLoader::BeginPlay()
{
	Super::BeginPlay();
	//UGameplayStatics::OpenLevel(this, LevelName);
	//FName d = "" + NameToLoad->GetName();
}

// Called every frame
void ALevelLoader::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	//if(GlobalVariableAccess)
	//{ 
		BlackboardComp->InitializeBlackboard(*(GlobalVariableAccess->BlackboardAsset));
	//}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "tick");
}
//OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult &, SweepResult
/*void ALevelLoader::OnHit(UPrimitiveComponent* HitComp, AActor* Actor, UPrimitiveComponent* Other, FVector Impulse, const FHitResult & Hit)
{
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "clition");
	//UE_LOG(LogTemp, Warning, TEXT("Your message"));
	//UGameplayStatics::OpenLevel(this, LevelName);//"levelLoader");
}*/

void ALevelLoader::OnOverLapB(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherActor->IsA(APlayerCharacter::StaticClass())) {
			if (LevelName != "None") {
				BlackboardComp->SetValueAsName(LevelKey, LevelName);
				/*APlayerCharacter* temp = Cast<APlayerCharacter>(OtherActor);
				temp->currentLevel = LevelName;*/
				UGameplayStatics::OpenLevel(this, LevelName);
			}
			else {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Level Name can't equal None");
			}
		}
	}
	/*if (OtherActor->IsA(Atest3Projectile::StaticClass())) {
	health--;
	if (health <= 0) {
	Destroy();
	}
	}*/
}