#include "BF_1.h"
#include "OrGate.h"


OrGate::OrGate()
{
}


OrGate::~OrGate()
{
}

void OrGate::PlugInTo(PowerObject* Plug)
{
	if (InPut.size() == 0) {
		InPut.push_back(Plug); //InPut[0] = InPutOne;
		Plug->WiredOutOf(this);
	}
	else if (InPut.size() == 1)
	{
		InPut.push_back(Plug);
		Plug->WiredOutOf(this);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "OrGate Plugged Into Too Many Plugs");
	}

	Update();
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
	if (InPut.size() > 1) {
		if (InPut[0]->IsOn() || InPut[1]->IsOn()) {
			SetState(true);
		}
		else {
			SetState(false);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "OrGate doesn't have enought Plugs");
	}
	//UpdateOuts();
}