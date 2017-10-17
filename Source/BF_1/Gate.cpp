// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "Gate.h"

Gate::Gate()
{
}

Gate::~Gate()
{
}

/*over ride this cause it always returns false*/
bool Gate::OutPut(bool InputOne, bool InputTwo) 
{
	return false;
}