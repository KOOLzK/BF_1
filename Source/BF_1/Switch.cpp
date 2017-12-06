#include "BF_1.h"
#include "Switch.h"


Switch::Switch() //should switch have a pramiter that asks for its starting state
{
}


Switch::~Switch()
{
}

void Switch::PlugInTo(PowerObject* Plug) //take this away, is the base class good enough?
{
	if (InPut.size() > 0) {
		InPut[0] = Plug;
	}
	else {
		InPut.push_back(Plug);
	}
	Update();
	//Plug->OutPut.push_back(this);
	
	//mState = Plug->IsOn();
}

void Switch::Update()
{
	if (InPut[0]->IsOn() && Toggle) {
		mState = true;
	}
	else {
		mState = false;
	}

	/*for (int i = 0; OutPut.size() > i; i++) {
		OutPut[i]->Update();
	}*/
	UpdateOuts();
}
bool Switch::IsOn()
{
	//return InPut[0]->IsOn(); //change to "return mState" maybe
	/*if (InPut[0]->IsOn() && Toggle) {
		mState = true;
	}
	else
	{
		mState = false;
	}*/

	return mState;

}

void Switch::Flip()
{
	Toggle = !Toggle;
	Update();
}