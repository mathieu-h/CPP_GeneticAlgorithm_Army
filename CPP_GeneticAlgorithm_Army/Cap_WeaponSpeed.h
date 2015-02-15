#pragma once
#include "Capacity.h"

class Cap_WeaponSpeed : public Capacity
{
public:
	
	// WeaponSpeed value must be init at 0 , and at each shot the value is set at maxReloadTime. Then it is decreased each turn to 0 (and then you shoot)
	Cap_WeaponSpeed() : Capacity() {
		updateValue();
		_value = 0;
	}

	void updateValue(){
		_maxReloadTime = (float)(1000/_level+1);
	}

	// add method to update currentValue  

private:
	float _maxReloadTime;
};

