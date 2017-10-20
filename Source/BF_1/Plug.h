// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PowerBar.h"

/**
 * 
 */
class BF_1_API Plug
{
public:
	Plug();
	~Plug();

	class PowerBar Source;

	bool isOn; // as a getter

	bool getIsOn();

};
