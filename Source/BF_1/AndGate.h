// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Gate.h" 

/**
 * 
 */
class BF_1_API AndGate : public Gate
{
public:
	AndGate();
	~AndGate();

	bool OutPut(bool InputOne, bool InputTwo) override;

};
