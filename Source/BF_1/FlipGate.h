// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include <vector>
#include "PowerObject.h"
/**
 * 
 */
class BF_1_API FlipGate : public PowerObject
{
public:
	FlipGate();
	~FlipGate();

	void PlugInTo(PowerObject* Plug) override;

	virtual void Update() override;

	std::vector <bool> Check;
};
