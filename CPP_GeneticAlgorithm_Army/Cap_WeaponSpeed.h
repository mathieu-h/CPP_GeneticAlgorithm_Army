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
		_maxReloadTime = (float)(100/(_level+1));
	}

	/*
	void setValue(float value){
		_value = value;
	} 
	*/
	void resetValue(){
		_value = _maxReloadTime;
	}

	void decrementReloadTime(){
		if(_value!=0) _value -= 1;
	}

private:
	float _maxReloadTime;
};

