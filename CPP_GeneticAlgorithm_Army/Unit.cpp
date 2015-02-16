#include "stdafx.h"
#include "Unit.h"


Unit::Unit(int globalLevel)
{
	//set random IA code
	//distribute level among capacities
}


Unit::~Unit()
{
}

void Unit::refresh(){
	_health.updateValue();
	_health.setValue(_health.getValue() + _healthRegen.getValue());
	_weaponSpeed.decrementReloadTime();
}

bool Unit::shoot(){
	if (_weaponSpeed.getValue() == 0){
		_weaponSpeed.resetValue();
		return true;
	}
	else{
		return false;
	}
}

void Unit::takeDamage(float damageValue){
	_health.setValue(damageValue-_armor.getValue());
}

void Unit::setPosition(Point& position){
	_position = position;
}

bool Unit::isAlive(){
	if (_health.getValue() <= 0){
		return false;
	}
	else{
		return true;
	}
}

Capacity& Unit::operator[](int index){
	switch (index){
		case 0:
			return _speed;
		case 1:
			return _health;
		case 2:
			return _armor;
		case 3:
			return _healthRegen;
		case 4:
			return _damage;
		case 5:
			return _range;
		case 6:
			return _weaponSpeed;
		default:
			break;
	}
}