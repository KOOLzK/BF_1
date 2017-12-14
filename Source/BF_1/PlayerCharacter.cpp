// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "PlayerCharacter.h"
#include "LightSwitch.h"
#include "SwingingDoor.h"
#include "InteractAble.h"
#include "PhysicsInteract.h"
#include "AIPatrol.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
//#include "MaterialInstance.generated.h"
#include "PhysicsInteract.h"
#include "PowerObject.h"

#define EEC_InteractAble ECollisionChannel::ECC_GameTraceChannel1


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//PowerObject* Po = new PowerObject();
	UCapsuleComponent*  CapsuleComponent = GetCapsuleComponent(); 
	GetCapsuleComponent()->BodyInstance.SetCollisionProfileName("Player");
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapBegin);//->OnComponentBeginOverlap(this, APlayerCharacter::BeginPlay());
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapEnd);
	GetCapsuleComponent()->SetCollisionResponseToChannel(EEC_InteractAble, ECollisionResponse::ECR_Ignore);


	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	PlayerCamera->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepWorldTransform);
	PlayerCamera->RelativeLocation = FVector(0, 0, 64.f);
	PlayerCamera->bUsePawnControlRotation = true;


	HandOffsetDepthX = 50.f;

	HandOffsetThorwX = 0;

	ChargingThrow = false;

	HandOffsetWidthY = 20.f;

	HandOffsetActiveZ = -10.0f;

	HandOffsetInactiveZ = -20.0f;

	IsRightHandActive = true;

	//attach heads to Camera
	RightHeadOffset = CreateDefaultSubobject<USceneComponent>(TEXT("RightHeadOffset"));
	RightHeadOffset->AttachToComponent(PlayerCamera, FAttachmentTransformRules::KeepWorldTransform);
	RightHeadOffset->RelativeLocation = FVector(HandOffsetDepthX, HandOffsetWidthY, HandOffsetActiveZ);

	LeftHeadOffset = CreateDefaultSubobject<USceneComponent>(TEXT("LeftHeadOffset"));
	LeftHeadOffset->AttachToComponent(PlayerCamera, FAttachmentTransformRules::KeepWorldTransform);
	LeftHeadOffset->RelativeLocation = FVector(HandOffsetDepthX, -HandOffsetWidthY, HandOffsetInactiveZ);


	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->Intensity = 3000.f;
	PointLight->bVisible = true;
	PointLight->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepWorldTransform);



	currentSwitch = nullptr;

	//back up in case it isn't set
	currentLevel = "puzzle1";

	LevelKey = "CurrentLevel";

	MyMaxWalkSpeed = 500;
	GetCharacterMovement()->MaxWalkSpeed = MyMaxWalkSpeed;

	ZLevelRestart = -10000;
	//BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	Targeting = NULL;

	Hidden = false;

	static ConstructorHelpers::FObjectFinder<UTexture2D> PS1(TEXT("Texture2D'/Engine/EditorMaterials/TargetIcon.TargetIcon'"));
	ReticleDisplayTarget = PS1.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> PS2(TEXT("Texture2D'/Game/Textures/HandIcon2.HandIcon2'"));
	ReticleDisplayInteract = PS2.Object;
	
	static ConstructorHelpers::FObjectFinder<UTexture2D> PS3(TEXT("Texture2D'/Game/Textures/SkullIcon.SkullIcon'"));
	ReticleDisplayDeath = PS3.Object;
	
	ReticleDisplayCurrent = ReticleDisplayTarget;

	HUDWidth = 64.0f;

	HUDHeight = 64.0f;

	dead = false;

	PlayerReach = 500.0f;

	ThrowStrength = 10000.0f;
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

	if (GetActorLocation().Z < ZLevelRestart)
	{
		//Death(); don't work anymore, seens i added the delay, so i use ReloadLevel() directly now
		ReloadLevel();
	}


	//Ray Trace
	HitResult = new FHitResult();
	StartTrace = PlayerCamera->GetComponentLocation();
	ForwardVector = PlayerCamera->GetForwardVector();
	EndTrace = ((ForwardVector * PlayerReach) + StartTrace); //1000 is to far
	TraceParams = new FCollisionQueryParams();

	if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, EEC_InteractAble, *TraceParams))
	{
		//check if ray trace storage is the not the same or NULL as Trace Result
		if (Targeting != Cast<AInteractAble>(HitResult->GetActor())) {
			//check if ray trace storage is empty
			if (Targeting) {
				//turns off glowing
				Targeting->Unfocused();
				//replace actor to ray trace storage
				Targeting = Cast<AInteractAble>(HitResult->GetActor());
				//change HUD
				ReticleDisplayCurrent = ReticleDisplayTarget;
			}
			else {
				//add actor to ray trace storage
				Targeting = Cast<AInteractAble>(HitResult->GetActor());
				//turns on glowing
				Targeting->Focused();
				//change HUD
				ReticleDisplayCurrent = ReticleDisplayInteract;
				//Debug
				if (DisplayDebugMessages) {
					DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(255, 0, 0), false, 5.f);
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("You Hit: %s"), *HitResult->Actor->GetName()));
				}
			}
		}
	}
	else {
	//if ray trace storage is full(it only holds one)
		if (Targeting) {
			//turns off glowing
			Targeting->Unfocused();
			//clear ray trace storage
			Targeting = NULL;
			//change HUD
			ReticleDisplayCurrent = ReticleDisplayTarget;
		}
	}


	//give player location to the Material Parameter Collections
	//FScalarParameterValue;
	//FCollectionScalarParameter;


	//add 2 second delay before increcing the force so the player can just drop the item
	if (ChargingThrow) {
		HandOffsetThorwX += ThrowStrength;//why does this number need to be so big for me to see an effect
		float ThrowPullBack = HandOffsetDepthX - (HandOffsetThorwX / ThrowStrength);
		/*maybe the number its > should take into account how big the object is so it doesn't clip 
		through the camera or be affected be the players hitbox*/
		if (ThrowPullBack > 15) {
			if (IsRightHandActive) {
				if (RightHead != NULL) {
					RightHeadOffset->RelativeLocation = FVector(ThrowPullBack, HandOffsetWidthY, HandOffsetActiveZ);
				}
			}
			else {
				if (LeftHead != NULL) {
					LeftHeadOffset->RelativeLocation = FVector(ThrowPullBack, -HandOffsetWidthY, HandOffsetActiveZ);
				}
			}
		}
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
	InputComponent->BindAction("DebugMessage", IE_Pressed, this, &APlayerCharacter::ToggleDebugMessages);
	InputComponent->BindAction("ActiveHand", IE_Pressed, this, &APlayerCharacter::ActiveHand);
	//InputComponent->BindAction("ActiveHand", IE_Released /*this is not necessary but Nice To Have, what it is supposed to do is when the player holds down the swop button both hand are active so they can drop or throw both items at the same time*/
	InputComponent->BindAction("EmptyHand", IE_Pressed, this, &APlayerCharacter::EmptyHandCharge);
	InputComponent->BindAction("EmptyHand", IE_Released, this, &APlayerCharacter::EmptyHand);
}

void APlayerCharacter::MoveForward(float val)
{
	if (!dead) {
		FRotator Rotation(0, GetActorRotation().Yaw, 0);
		FVector Forward = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Forward, val);
	}
}

void APlayerCharacter::MoveRight(float val)
{
	if (!dead) {
		FRotator Rotation(0, GetActorRotation().Yaw, 0);
		FVector Right = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Right, val);
	}
}

void APlayerCharacter::LookYaw(float val)
{
	if (!dead) {
		AddControllerYawInput(val);
	}
}

void APlayerCharacter::LookPitch(float val)
{
	if (!dead) {
		AddControllerPitchInput(val);
	}
}

void APlayerCharacter::Use()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "E");
	if (currentSwitch != nullptr)
	{
		currentSwitch->Switching();
	}

	if (currentDoor != nullptr)
	{
		currentDoor->Use();
	}

	if (Targeting != NULL) 
	{
		//check HasPhysics true
		if (Targeting->HasPhysics) {
			if (IsRightHandActive) {
				if (RightHead == NULL) {
					//empty hand so pick it up
					RightHead = Targeting;
					RightHead->AttachToHead(RightHeadOffset);
					RightHead->SetActorRelativeLocation(FVector(0, 0, 0));
				}
				else {
					//drop one item to pick up another
					RightHead->DetachFromHead();
					RightHead = Targeting;
					RightHead->AttachToHead(RightHeadOffset);
					RightHead->SetActorRelativeLocation(FVector(0, 0, 0));
				}
			}
			else 
			{
				if (LeftHead == NULL) {
					//empty hand so pick it up
					LeftHead = Targeting;
					LeftHead->AttachToHead(LeftHeadOffset);
					LeftHead->SetActorRelativeLocation(FVector(0, 0, 0));
				}
				else {
					//drop one item to pick up another
					LeftHead->DetachFromHead();
					LeftHead = Targeting;
					LeftHead->AttachToHead(LeftHeadOffset);
					LeftHead->SetActorRelativeLocation(FVector(0, 0, 0));
				}
			}
		}
		else //check HasPhysics false
		{
			if (RightHead != NULL) {
				//temp door and key
				if (Targeting->ItemName == RightHead->ItemName) {
					Targeting->UpdateAndDelete();
					RightHead->Destroy();
					//FStat_STAT_Navigation_RecastBuildNavigation();
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Wrong Item");// +Targeting->ItemName.ToString);
				}
			}
			else 
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "You need Key");
			}
		}
		
	}
	/*else //this will be moved to its own function for dropping things
	{
		if (RightHead != NULL)
		{
			RightHead->DetachFromHead();
			RightHead = NULL; //i should check to see if i need this
		}
	}*/

}


void APlayerCharacter::ActiveHand()
{
	IsRightHandActive = !IsRightHandActive;

	if(IsRightHandActive){
		RightHeadOffset->RelativeLocation = FVector(HandOffsetDepthX, HandOffsetWidthY, HandOffsetActiveZ);
		LeftHeadOffset->RelativeLocation = FVector(HandOffsetDepthX, -HandOffsetWidthY, HandOffsetInactiveZ);
	}else{
		RightHeadOffset->RelativeLocation = FVector(HandOffsetDepthX, HandOffsetWidthY, HandOffsetInactiveZ);
		LeftHeadOffset->RelativeLocation = FVector(HandOffsetDepthX, -HandOffsetWidthY, HandOffsetActiveZ);
	}
}

void APlayerCharacter::EmptyHand()
{
	if(IsRightHandActive){
		if (RightHead != NULL)
		{
			RightHead->DetachFromHead();
			APhysicsInteract* temp = Cast<APhysicsInteract>(RightHead);
			//temp->CollisionComp->AddForce(PlayerCamera->GetForwardVector() * 1000);
			//RightHead->GetRootComponent()->ComponentVelocity = ForwardVector * 1000;
			//RightHead->GetRootComponent()->SetPhysicsVolume;
			//SetPhysicsLinearVelocity
			RightHead = NULL;
			temp->CollisionComp->AddForce(PlayerCamera->GetForwardVector() * HandOffsetThorwX);//*1000000
			RightHeadOffset->RelativeLocation = FVector(HandOffsetDepthX, HandOffsetWidthY, HandOffsetActiveZ);
		}
	}else{
		if (LeftHead != NULL)
		{
			LeftHead->DetachFromHead();
			APhysicsInteract* temp = Cast<APhysicsInteract>(LeftHead);
			temp->CollisionComp->AddForce(PlayerCamera->GetForwardVector() * HandOffsetThorwX);
			LeftHead = NULL;
			LeftHeadOffset->RelativeLocation = FVector(HandOffsetDepthX, -HandOffsetWidthY, HandOffsetActiveZ);
		}
	}
	HandOffsetThorwX = 0.0f;//+100000
	ChargingThrow = false;
}
void APlayerCharacter::EmptyHandCharge()
{
	ChargingThrow = true;
}

void APlayerCharacter::ToggleDebugMessages()
{
	DisplayDebugMessages = !DisplayDebugMessages;
	
	if (DisplayDebugMessages) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "DebugMessagesOn");
	}
}

void APlayerCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	// Other Actor is the actor that triggered the event. Check that is not ourself.
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		//probably replace this with a ray trace so the player can't hit a light switch behind them
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
	//i don't know if my own messages is more trouble then its worth, i wanted to show what it hit
	if (DisplayDebugMessages) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Begin");
	}
	
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
	if (DisplayDebugMessages) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "End");
	}
	
}

UTexture2D* APlayerCharacter::GetCurrentDispay()
{
	return ReticleDisplayCurrent;
}

float APlayerCharacter::GetHUDWidth()
{
	return HUDWidth;
}

float APlayerCharacter::GetHUDHeight()
{
	return HUDHeight;
}

UPointLightComponent* APlayerCharacter::GetLight()
{
	return PointLight;
}

void APlayerCharacter::Death()
{
	//change HUD
	ReticleDisplayCurrent = ReticleDisplayDeath;
	HUDWidth = 564.0f;
	HUDHeight = 564.0f;
	dead = true;

	GetWorldTimerManager().SetTimer(ReloadLevelDelay, this, &APlayerCharacter::ReloadLevel, 2.0f);
}

void APlayerCharacter::ReloadLevel()
{
	//load level again to reset it
	FString a = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(*a));
}





/*
Ref

HUD = https://www.youtube.com/watch?v=Snz99qBh9qQ


crap
//currentLevel = BlackboardComp->GetValueAsName(LevelKey);//GetValueAsBool(LevelKey);
//UGameplayStatics::OpenLevel(this, currentLevel);
//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, a);




//FHitResult Hit(ForceInit);
//GetWorld()->QueryTraceData()

//In player controller class

//location the PC is focused on
const FVector Start = GetFocalLocation();

//256 units in facing direction of PC (256 units in front of the camera)
const FVector End = Start + GetControlRotation().Vector() * 256;

//The trace data is stored here
FHitResult HitData(ForceInit);

//If Trace Hits anything
if (UMyStaticFunctionLibrary::Trace(GetWorld(), GetPawn(), Start, End, HitData))
{
//Print out the name of the traced actor
if (HitData.GetActor())
{
ClientMessage(HitData.GetActor()->GetName());

//Print out distance from start of trace to impact point
ClientMessage("Trace Distance: " + FString::SanitizeFloat(HitData.Distance));
}
}


if (GlobalVariableAccess)
{
BlackboardComp->InitializeBlackboard(*(GlobalVariableAccess->BlackboardAsset));
}
else
{
GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "NO");
}


//RightHeadOffset2 = CreateDefaultSubobject<UActorComponent>(TEXT("RightHeadOffset"));
//RightHeadOffset2->AttachToComponent(PlayerCamera, FAttachmentTransformRules::KeepWorldTransform);
//RightHeadOffset2->RelativeLocation = FVector(50.f, 20.f, 0);

//GetCapsuleComponent()->bGenerateOverlapEvents = true;
//GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);


*/