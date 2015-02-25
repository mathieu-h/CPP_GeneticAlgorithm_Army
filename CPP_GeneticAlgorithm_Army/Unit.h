#pragma once
#include "Capacity.h"
#include "Cap_Armor.h"
#include "Cap_Damage.h"
#include "Cap_Health.h"
#include "Cap_HealthRegen.h"
#include "Cap_Range.h"
#include "Cap_Speed.h"
#include "Cap_WeaponSpeed.h"
#include <math.h>
#include "Point.h"
#include <vector>


class Unit
{
public:
	static int _idCounter;
	Unit(int globalLevel);
	Unit(IACode iaCode, std::vector<int> levels);
	~Unit();

	const Cap_Armor& getArmor(){ return _armor; };
	const Cap_Damage& getDamage(){ return _damage; };
	const Cap_Health& getHealth() { return _health; };
	const Cap_HealthRegen& getHealthRegen(){ return _healthRegen; };
	const Cap_Range& getRange(){ return _range; };
	const Cap_Speed& getSpeed(){ return _speed; };
	const Cap_WeaponSpeed& getWeaponSpeed(){ return _weaponSpeed; };

	int getLevel();
	Point getPosition() const{ return _position; };
	int getId() const { return _id; };
	IACode getIACode() const{ return _iaCode; };

	void setPosition(Point& position);
	void refresh();
	bool shoot();
	bool canShoot() const;
	void takeDamage(float value);
	bool isAlive();

	Capacity& operator[](int index);


private:
	int _id;
	Cap_Armor _armor;
	Cap_Damage _damage;
	Cap_Health _health;
	Cap_HealthRegen _healthRegen;
	Cap_Range _range;
	Cap_Speed _speed;
	Cap_WeaponSpeed _weaponSpeed;
	Point _position;
	IACode _iaCode;
};
