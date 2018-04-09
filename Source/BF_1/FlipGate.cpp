// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "FlipGate.h"

FlipGate::FlipGate()
{
}

FlipGate::~FlipGate()
{
}

void FlipGate::PlugInTo(PowerObject* Plug)
{
	if (InPut.size() > 0) {
		InPut[0] = Plug;
		bool temp = Plug->IsOn();
		Check[0] = temp;//true;
	}
	else
	{
		InPut.push_back(Plug);
		bool temp = Plug->IsOn();
		Check.push_back(temp);
	}

	Plug->WiredOutOf(this);

	Update();
}

void FlipGate::Update()
{
	//if anything changes then change this one
	for (int i = 0; i < InPut.size(); i++) {
		if (Check[i] != InPut[i]->IsOn()) {
			SetState(!IsOn());
			Check[i] = InPut[i]->IsOn();
		}
	}

	/*if (InPut[0]->IsOn()) {
		SetState(false);
	}
	else {
		SetState(true);
	}*/

	//UpdateOuts();
}