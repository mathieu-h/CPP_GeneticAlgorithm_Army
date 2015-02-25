#include "stdafx.h"
#include "Unit.h"


Unit::Unit(int globalLevel)
{
	//set random IA code	
	_iaCode = (IACode)(rand() % 15);
	//distribute level among capacities randomly
	for (int i = 0; i < globalLevel; i++){
		((*this)[rand() % 7]).upgrade();
	}
	//_id = ++Unit::_idCounter;
}

Unit::Unit(IACode iaCode, std::vector<int> levels)
{
	//set random IA code	
	_iaCode = iaCode;
	//distribute level among capacities with the given vector of levels
	for (int i = 0; i < levels.size(); i++){
		((*this)[i]).upgrade(levels[i]);
	}
	//_id = ++Unit::_idCounter;
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

int Unit::getLevel(){
	int globalLevel = 0;
	for (int i = 0; i <= 6; i++){
		globalLevel += ((*this)[i]).getCLevel();
	}
	return globalLevel;
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
			return _speed;
			break;
	}
}