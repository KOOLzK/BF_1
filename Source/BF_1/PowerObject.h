// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <vector>
#include "PG_Subject.h"

/**
 * 
 */
class BF_1_API PowerObject : public PG_Subject
{
public:
	PowerObject();
	~PowerObject();

	virtual bool IsOn();

	virtual void PlugInTo(PowerObject* Plug);

	virtual void WiredOutOf(PowerObject* Wired);

	virtual void Update();

	virtual void UpdateOuts();

	int OutPutSize();

	virtual void Flip();

	bool Toggle;

	float PowerPercent;

	void PassUpdate(int (*func) (void));

	//(*func) (*func);

	class ABlinkingLight* ifLight;

	void AttachLight(ABlinkingLight* AL);

protected:
	bool mState;
	bool mPreUpdateState;

	std::vector <PowerObject*> InPut;
	std::vector <PowerObject*> OutPut;

	void SetState(bool state);

};
