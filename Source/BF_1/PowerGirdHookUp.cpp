// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "PowerGirdHookUp.h"


APowerGirdHookUp::APowerGirdHookUp() 
{

	/*static ConstructorHelpers::FObjectFinder<UTexture2D> PowerTexture(TEXT("Texture2D'/Game/Textures/PowerSymbol.PowerSymbol'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> LightTexture(TEXT("Texture2D'/Game/Textures/PowerLight.PowerLight'"));*/

}

void APowerGirdHookUp::HookingUp()
{
	for (int i = 0; HookUp.Num() > i; i++) {
		if (HookUp[i] != NULL) {
			if (HookUp[i]->IsA(APowerGirdHookUp::StaticClass())) {
				APowerGirdHookUp* temp = Cast<APowerGirdHookUp>(HookUp[i]);
				temp->PO->PlugInTo(PO);
			}
		}
	}
}