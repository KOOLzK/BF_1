// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * shit that unreal should have taken care of for me   - karl
 */
class BF_1_API VariableTypeConverter
{
public:
	VariableTypeConverter();
	~VariableTypeConverter();

	/*Full numbers only*/
	int FStringToInt(FString InputNumber);

	FString negative;
	FString zero;
	FString one;
	FString two;
	FString three;
	FString four;
	FString five;
	FString six;
	FString seven;
	FString eight;
	FString nine;

};
