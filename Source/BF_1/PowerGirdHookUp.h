// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PG_Observer.h"
#include "PowerGirdHookUp.generated.h"

/**
 * 
 */
UCLASS()
class BF_1_API APowerGirdHookUp : public APG_Observer
{
	GENERATED_BODY()
	
public:

	APowerGirdHookUp();

	class PowerObject* PO;
	
	/*UPROPERTY(VisibleAnywhere, Category = ID)//, AdvancedDisplay, meta = (EditCondition = "HookUp"))
	bool HasPower;*/

	/*these are meant to be PowerGirdHookUp or PG_*/
	UPROPERTY(EditAnywhere, Category = ID)//, AdvancedDisplay)
	TArray<AActor*> HookUp;

	TArray<UArrowComponent*> ArrowDisplay;

	void HookingUp();

	void DisplayingArrows();

	bool BillboardVisible;

	UPROPERTY(EditAnywhere, Category = Collision)
	UBillboardComponent* EditorIcon;

	UPROPERTY(EditAnywhere, Category = Collision)
	UTexture2D* PowerTexture;

	/*UPROPERTY(EditAnywhere, Category = Collision)
	UTexture2D* LightTexture;*/

	
};
