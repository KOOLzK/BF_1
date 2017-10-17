// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "AndGate.h"

AndGate::AndGate()
{
}

AndGate::~AndGate()
{
}

bool AndGate::OutPut(bool InputOne, bool InputTwo)
{
	if (InputOne && InputTwo) {
		return true;
	}
	else
	{
		return false;
	}
}