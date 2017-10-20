// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PowerObject.h"

/**
 * 
 */

//ISA PowerObject
class BF_1_API Toggle : public PowerObject
{
public:
	Toggle();
	~Toggle();

	// toggleState: Boolean

	bool toggleState;

	bool isON() override;

	void changeToggle(bool newState);

	void flip();
	/*
	 override isON(){ //what am i overriding PowerObject didn't have a isOn function. well it does now
		return input.isOn && toggleState
	 }

	publc function changeToggle(newState:Boolean){
		toggleState=newState
	 }

	 public function flip(){
		toggleState = !toggleState
	 }

	 */
};
