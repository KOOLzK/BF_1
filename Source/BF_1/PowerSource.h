// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PowerObject.h"

/**
 * 
 */
class BF_1_API PowerSource : public PowerObject
{
public:
	PowerSource();
	~PowerSource();

	bool isOn() override;
	//override isON(){ return true; }
};
