#include "BF_1.h"
#include "OrGate.h"


OrGate::OrGate()
{
}


OrGate::~OrGate()
{
}

void OrGate::PlugInTo(PowerObject* InPutOne, PowerObject* InPutTwo)
{
	if (InPut.size() > 0) {
		InPut[0] = InPutOne;
	}
	else
	{
		InPut.push_back(InPutOne);
	}

	if (InPut.size() > 1) {
		InPut[1] = InPutTwo;
	}
	else
	{
		InPut.push_back(InPutTwo);
	}
	InPutOne->WiredOutOf(this);
	InPutTwo->WiredOutOf(this);

	Update();
}

void OrGate::Update()
{
	if (InPut[0]->IsOn() || InPut[1]->IsOn()) {
		mState = true;
	}
	else {
		mState = false;
	}

	UpdateOuts();
}