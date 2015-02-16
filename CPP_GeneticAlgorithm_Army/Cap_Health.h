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
	}

	// add method to update _value

	void setValue(float value){
		_value = value;
	}

	void takeDamage(float value){
		_value -= value;
	}

	void resetValue(){
		_value = _maxLife;
	}
private:
	float _maxLife;
};

