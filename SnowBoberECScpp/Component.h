#pragma once
#include "CmpId.h"

struct Component
{
public:
	unsigned int id;

	Component(unsigned int i);

	virtual int getId();
};

