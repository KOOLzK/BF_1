// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractCube.h"
#include "PG_CardReader.generated.h"

/**
 * 
 */
UCLASS()
class BF_1_API APG_CardReader : public AInteractCube
{
	GENERATED_BODY()
	
public:

	APG_CardReader();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void InteractWithPlayer() override;
	
	UFUNCTION(BlueprintCallable, Category = ID)
	void SetCardLevel(int Level);

	UFUNCTION(BlueprintCallable, Category = ID)
	int GetRequiredLevel();

	UFUNCTION(BlueprintCallable, Category = ID)
	void BPFlipState();

	//card level required
	UPROPERTY(EditAnywhere, Category = ID)
	int CardLevel;

	UPROPERTY(EditAnywhere, Category = ID)
	int CardLevelRequired;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UMaterial* SwitchMaterial1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UMaterial* SwitchMaterial2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	class UStaticMeshComponent* LightDisplay;


};
