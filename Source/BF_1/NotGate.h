#pragma once
#include "PowerObject.h"
class BF_1_API NotGate : public PowerObject
{
public:
	NotGate();
	~NotGate();

	void PlugInTo(PowerObject* Plug) override;

	virtual void Update() override;
};

