#pragma once
#include "PowerObject.h"
class BF_1_API OrGate : public PowerObject
{
public:
	OrGate();
	~OrGate();

	void PlugInTo(PowerObject* InPutOne, PowerObject* InPutTwo);

	virtual void Update() override;
};

