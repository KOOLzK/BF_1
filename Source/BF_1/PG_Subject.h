// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include <iostream>
#include <vector>
#include "PG_Observer.h"

/**
 * 
 */
class BF_1_API PG_Subject
{
public:
	PG_Subject();
	~PG_Subject();

	std::vector < class APG_Observer * > views;
	bool value;

	void Attach(APG_Observer *obs);

	void SetVal(bool val);

	bool GetVal();

	void Notify();
};
