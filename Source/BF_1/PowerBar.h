// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Gate.h"

#include "PowerConnection.h"

/**
 * 
 */
 
 //IS A POWER OBJECT
class BF_1_API PowerBar : public PowerObject
{
public:
	PowerBar();
	~PowerBar();

	PowerConnection in;
	PowerConnection out[5];

	//in:powerConnection, PowerSource
	//out[]:powerConnection array of connections



	class Gate gate;
};
