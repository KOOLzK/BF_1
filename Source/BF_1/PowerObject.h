// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PowerConnection.h"
/*
To Jeff

next time we meet i think we need to have a philosophical debate or at least a design debate. i draw
some pictures and wrote some stuff on the power gird, that we can talk about wednesday.

P.S.
i hope you meant it when you said this code doesn't have to work

Form Karl
*/

/**
 * 
 */


class BF_1_API PowerObject
{
public:
	PowerObject();
	~PowerObject();

protected:
	class PowerConnection _inputs[5]; //error with out the '5' ("incomplete type is not allowed"). 
									//also should this be a list?
	class PowerConnection _outputs[5]; // no error here for some reason

	bool isOn;

	virtual bool isOn();
	//protected _inputs[]:PowerConnections
	//protected _outputs[]:PowerConnections
};
