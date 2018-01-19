#include "BF_1.h"
#include "AndGate.h"


AndGate::AndGate()
{
}


AndGate::~AndGate()
{
}

void AndGate::PlugInTo(PowerObject* Plug) 
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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "AndGate Plugged Into Too Many Plugs");
	}

	Update();
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
	if(InPut.size() > 1){
		if (InPut[0]->IsOn() && InPut[1]->IsOn()) {
			SetState(true);
		}
		else {
			SetState(false);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "AndGate doesn't have enought Plugs");
	}
	//this->PowerObject::Update();
	/*for (int i = 0; OutPut.size() > i; i++) {
		OutPut[i]->Update();
	}*/
	//UpdateOuts();
}
/*bool AndGate::IsOn()
{
	return mState;
}*/