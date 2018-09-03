// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "VariableTypeConverter.h"

VariableTypeConverter::VariableTypeConverter()
{
	negative = "-";
	zero = "0";
	one = "1";
	two = "2";
	three = "3";
	four = "4";
	five = "5";
	six = "6";
	seven = "7";
	eight = "8";
	nine = "9";
}

VariableTypeConverter::~VariableTypeConverter()
{
}

int VariableTypeConverter::FStringToInt(FString InputNumber)
{
	int length = InputNumber.Len();
	for(int DecimalPlace = 0; DecimalPlace < length; DecimalPlace++){
		FString OneChar = InputNumber.Mid(DecimalPlace-1,1);
		
		if(OneChar.Equals("-")){
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "negative");
			return -3;
		}
		if (OneChar.Equals(zero)) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "zero");
			return 0;
		}
		return -2;
	}
	return -1;
}
