#include "BF_1.h"
#include "AndGate.h"


AndGate::AndGate()
{
}


AndGate::~AndGate()
{
}

void AndGate::PlugInTo(PowerObject* InPutOne, PowerObject* InPutTwo)
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
	//InPut.push_back(InPutTwo);
	Update();
}

void AndGate::Update()
{
	if (InPut[0]->IsOn() && InPut[1]->IsOn()) {
		mState = true;
	}
	else {
		mState = false;
	}
	//this->PowerObject::Update();
	/*for (int i = 0; OutPut.size() > i; i++) {
		OutPut[i]->Update();
	}*/
	UpdateOuts();
}
bool AndGate::IsOn()
{
	return mState;
}