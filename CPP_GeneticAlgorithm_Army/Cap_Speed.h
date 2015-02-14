#pragma once
#include "Capacity.h"

class Cap_Speed : public Capacity
{
public:
	void updateValue()
	{
		_value = (float)_level + 1;
	}
};

