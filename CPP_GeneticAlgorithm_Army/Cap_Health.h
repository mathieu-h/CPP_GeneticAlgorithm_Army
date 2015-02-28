#pragma once
#include "Capacity.h"

class Cap_Health : public Capacity
{
public:
	
	Cap_Health() : Capacity() {
		updateValue();
		_value = _maxLife;
	}

	void updateValue(){
		_maxLife = (float)((1 + _level) * 10);
		_value = _maxLife;
	}
	// add method to update _value
	/*
	void setValue(float value){
		_value = value;
		if (value < 0) value = 0;
	}
	*/
	void takeDamage(float value){
		_value -= value;
		if (_value < 0) _value = 0;
	}

	void resetValue(){
		_value = _maxLife;
	}
private:
	float _maxLife;
};

