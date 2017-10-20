// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "Toggle.h"

// A toggle is a switch that can flip between on and off
Toggle::Toggle()
{
}

Toggle::~Toggle()
{
}

bool Toggle::isON()
{
	return (_inputs[0].isOn && toggleState);
}

void Toggle::changeToggle(bool newState)
{
	toggleState = newState;
}

void Toggle::flip()
{
	toggleState = !toggleState;
}