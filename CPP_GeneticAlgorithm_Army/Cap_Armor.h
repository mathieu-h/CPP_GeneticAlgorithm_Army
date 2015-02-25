#pragma once
#include "Capacity.h"

class Cap_Armor : public Capacity
{
public:

	void updateValue()
	{
		//_value = (float)_level * 2; oldval
		_value = (float)_level / 2;
	}
};

