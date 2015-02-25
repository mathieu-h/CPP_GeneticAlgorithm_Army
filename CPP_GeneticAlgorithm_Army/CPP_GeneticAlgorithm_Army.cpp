// CPP_GeneticAlgorithm_Army.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "Capacity.h"
#include "Army.h"
#include "Capacity.h"
#include "Action.h"
#include "IA.h"
#include "Point.h"
#include <ctime>
#include <vector>

int Unit::_idCounter = 0;

void executeAction(Action& action, Unit& currentUnit,Army& army){
	if (action.getType() == MOVE){
		currentUnit.setPosition(static_cast<ActionMove&>(action).getNextPosition());
		std::cout << "Move" << std::endl;
	}
	else if (action.getType() == SHOOT && currentUnit.shoot()){
		//currentUnit->setPosition(static_cast<ActionShoot&>(action).getUnitID());
		int targetID = static_cast<ActionShoot&>(action).getUnitID();
		Unit target = army.getUnit(targetID);
		target.takeDamage(currentUnit.getDamage().getValue());
		std::cout << "Shoot" << std::endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::srand(std::time(NULL));
	Army first_army = Army(3, 100);
	Army sec_army = Army(3, 100);
	first_army.setArmyInFormation(100);
	sec_army.setArmyInFormation(0);
	std::vector<Unit*> first_units = first_army.getUnitsList();
	std::vector<Unit*> sec_units = sec_army.getUnitsList();
	IA ia = IA();

	while (!first_army.isEmpty() && !sec_army.isEmpty()){
		if (first_army.size() == 2){
			std::cout << "KILL" << std::endl;
		}
		Unit* currentUnit = nullptr;
		if (rand())
		{
			currentUnit = first_units[rand() % first_units.size()];
			executeAction(ia(*currentUnit, first_army, sec_army), *currentUnit, sec_army);
			first_army.refreshUnits();
			sec_army.purge();
		}
		else
		{
			currentUnit = sec_units[rand() % sec_units.size()];
			executeAction(ia(*currentUnit, first_army, sec_army), *currentUnit, first_army);
			sec_army.refreshUnits();
			first_army.purge();
		}		
	}

	return 0;
}

