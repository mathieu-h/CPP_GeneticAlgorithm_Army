#pragma once
#include "Capacity.h"

class Cap_Damage : public Capacity
{
public:

	void updateValue()
	{
		_value = (float)_level * 2;
	}

};

