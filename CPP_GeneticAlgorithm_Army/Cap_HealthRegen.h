#pragma once
#include "Capacity.h"

class Cap_HealthRegen : public Capacity
{
public:
	void updateValue()
	{
		//_value = (float)_level * 3; oldval
		_value = (float)_level / 1000;
	}
};

