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

	const Cap_Armor& getArmor()const { return _armor; };
	const Cap_Damage& getDamage()const{ return _damage; };
	const Cap_Health& getHealth()const { return _health; };
	const Cap_HealthRegen& getHealthRegen()const{ return _healthRegen; };
	const Cap_Range& getRange()const{ return _range; };
	const Cap_Speed& getSpeed()const { return _speed; };
	const Cap_WeaponSpeed& getWeaponSpeed()const{ return _weaponSpeed; };

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

	void mutate();

	Capacity& operator[](int index);
	Unit* Unit::operator*(Unit& unit);

	std::string getIACodeName(const IACode IACode) const;


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

std::ostream& operator<<(std::ostream& out, const Unit& army);