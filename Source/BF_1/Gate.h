// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class BF_1_API Gate
{
public:
	Gate();
	~Gate();

	/*replace bool Inputs with Toggle Inputs?*/
	virtual bool OutPut(bool InputOne, bool InputTwo);

	bool isOn;
};
