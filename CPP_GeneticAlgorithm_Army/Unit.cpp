#include "stdafx.h"
#include "Unit.h"
#include <string>


Unit::Unit(int globalLevel)
{
	//set random IA code	
	_iaCode = (IACode)(rand() % 15);
	//distribute level among capacities randomly
	for (int i = 0; i < globalLevel; i++){
		((*this)[rand() % 7]).upgrade();
	}
	_id = ++_idCounter;
}

Unit::Unit(IACode iaCode, std::vector<int> levels)
{
	//set random IA code	
	_iaCode = iaCode;
	//distribute level among capacities with the given vector of levels
	for (int i = 0; i < levels.size(); i++){
		((*this)[i]).upgrade(levels[i]);
	}
	_id = ++_idCounter;
}

Unit::Unit(const Unit& unitToCopy){
	_id = unitToCopy._id;
	_armor = unitToCopy._armor;
	_damage = unitToCopy._damage;
	_health = unitToCopy._health;
	_healthRegen = unitToCopy._healthRegen;
	_range = unitToCopy._range;
	_speed = unitToCopy._speed;
	_weaponSpeed = unitToCopy._weaponSpeed;
	_position = unitToCopy._position;
	_iaCode = unitToCopy._iaCode;
}

Unit::~Unit()
{
}


void Unit::refresh(){
	//_health.updateValue();
	//_health.setValue(_health.getValue() + _healthRegen.getValue());
	_weaponSpeed.decrementReloadTime();
}

bool Unit::shoot(){
	if (_weaponSpeed.getValue() <= 0){
		_weaponSpeed.resetValue();
		return true;
	}
	else{
		return false;
	}
}


bool Unit::canShoot() const{
	if (_weaponSpeed.getValue() <= 0){
		//_weaponSpeed.resetValue();
		return true;
	}
	else{
		return false;
	}
}

void Unit::takeDamage(float damageValue){
	_health.takeDamage(damageValue-_armor.getValue());
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

std::string Unit::getIACodeName(const IACode IACode) const{
	
	switch (IACode)
	{
	case IACode::LD:
		return "LD";
	case IACode::HD:
		return "HD";
	case IACode::L0:
		return "L0";
	case IACode::H0:
		return "H0";
	case IACode::L1:
		return "L1";
	case IACode::H1:
		return "H1";
	case IACode::L2:
		return "L2";
	case IACode::H2:
		return "H2";
	case IACode::L3:
		return "L3";
	case IACode::H3:
		return "H3";
	case IACode::L4:
		return "L4";
	case IACode::H4:
		return "H4";
	case IACode::L5:
		return "L5";
	case IACode::H5:
		return "H5";
	case IACode::L6:
		return "L6";
	case IACode::H6:
		return "H6";

	default:
		return "";
	}
}


std::ostream& operator<<(std::ostream& out, const Unit& army){
	
	out << army.getSpeed().getCLevel();
	out << " ";
	out << army.getHealth().getCLevel();
	out << " ";
	out << army.getArmor().getCLevel();
	out << " ";
	out << army.getHealthRegen().getCLevel();
	out << " ";
	out << army.getDamage().getCLevel();
	out << " ";
	out << army.getRange().getCLevel();
	out << " ";
	out << army.getWeaponSpeed().getCLevel();
	out << " ";
	out << army.getIACodeName(army.getIACode());

	return out;
}