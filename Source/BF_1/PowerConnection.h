// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PowerObject.h"

/**
 * 
 */
//ISA POWEROBJECT
class BF_1_API PowerConnection : public PowerObject
{
public:
	PowerConnection();
	~PowerConnection();

	//in: PowerObject //Jeff Note: May not need this reflection
	//out: PowerObject

	PowerObject out;

	void onChange(bool isOn);
	/*
	function onChange(isOn:Boolean){
		alerts out of change
	}
	*/
};
