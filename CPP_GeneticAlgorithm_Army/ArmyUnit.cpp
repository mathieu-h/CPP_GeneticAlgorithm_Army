#include "stdafx.h"
#include "ArmyUnit.h"


ArmyUnit::ArmyUnit()
{
}


ArmyUnit::~ArmyUnit()
{
}


Capacity& ArmyUnit::operator[](int index){
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