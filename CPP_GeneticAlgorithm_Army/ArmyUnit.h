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

class ArmyUnit
{
public:
	ArmyUnit();
	~ArmyUnit();

	Cap_Armor& getArmor();
	Cap_Damage& getDamage();
	Cap_Health& getHealth();
	Cap_HealthRegen& getHealthRegen();
	Cap_Range& getRange();
	Cap_Speed& getSpeed();
	Cap_WeaponSpeed& getWeaponSpeed();

	int getLevel();
	Point getPosition();

private:
	int _id;
	Cap_Armor _armor;
	Cap_Damage _damage;
	Cap_Health _health;
	Cap_HealthRegen _healthRegen;
	Cap_Range _range;
	Cap_Speed _speed;
	Cap_WeaponSpeed _weaponSpeed;
};

