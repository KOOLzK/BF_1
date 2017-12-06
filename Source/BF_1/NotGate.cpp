#include "BF_1.h"
#include "NotGate.h"


NotGate::NotGate()
{
}


NotGate::~NotGate()
{
}

void NotGate::PlugInTo(PowerObject* Plug)
{
	if (InPut.size() > 0) {
		InPut[0] = Plug;
	}
	else
	{
		InPut.push_back(Plug);
	}

	Plug->WiredOutOf(this);

	Update();
}

void NotGate::Update()
{
	if (InPut[0]->IsOn()) {
		mState = false;
	}
	else {
		mState = true;
	}

	UpdateOuts();
}