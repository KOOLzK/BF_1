#pragma once
#include "PowerObject.h"
class BF_1_API AndGate : public PowerObject

{
public:
	AndGate();
	~AndGate();

	void PlugInTo(PowerObject* Plug) override;

	void PlugInTo(PowerObject* InPutOne, PowerObject* InPutTwo);

	virtual void Update() override;

	//bool IsOn() override;
};

