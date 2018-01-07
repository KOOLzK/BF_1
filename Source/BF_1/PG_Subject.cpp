// Fill out your copyright notice in the Description page of Project Settings.

#include "BF_1.h"
#include "PG_Subject.h"

PG_Subject::PG_Subject()
{
}

PG_Subject::~PG_Subject()
{
}

void PG_Subject::Attach(APG_Observer *obs)
{
	views.push_back(obs);
}

void PG_Subject::SetVal(bool val)
{
	value = val;
	Notify();
}

bool PG_Subject::GetVal()
{
	return value;
}

void PG_Subject::Notify()
{
	for (int i = 0; i < views.size(); i++) {
		views[i]->Update();
	}
}