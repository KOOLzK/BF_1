// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "PowerConnection.h"

PowerConnection::PowerConnection()
{
}

PowerConnection::~PowerConnection()
{
}

void PowerConnection::onChange(bool isOn) 
{
	out.isOn = isOn;
}