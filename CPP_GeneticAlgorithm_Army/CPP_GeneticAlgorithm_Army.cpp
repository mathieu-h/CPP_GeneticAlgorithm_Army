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



void executeAction(Action& action, Unit& currentUnit){
	if (action.getType() == MOVE){
		currentUnit.setPosition(static_cast<ActionMove&>(action).getNextPosition());
		std::cout << "Move" << std::endl;
	}
	else if (action.getType() == SHOOT){
		//currentUnit->setPosition(static_cast<ActionShoot&>(action).getUnitID());
		Unit target = static_cast<ActionShoot&>(action).getTarget();
		target.takeDamage(currentUnit.getDamage().getValue());
		std::cout << "Shoot" << std::endl;

	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::srand(std::time(NULL));
	Army first_army = Army(10, 10);
	Army sec_army = Army(10, 10);
	std::vector<Unit*> first_units = first_army.getUnitsList();
	std::vector<Unit*> sec_units = sec_army.getUnitsList();
	IA ia = IA();

	while (!first_army.isEmpty() && !sec_army.isEmpty()){
		Unit* currentUnit = nullptr;
		if (rand())
		{
			currentUnit = first_units[rand() % first_units.size()];
			executeAction(ia(*currentUnit, first_army, sec_army), *currentUnit);
			sec_army.purge();
		}
		else
		{
			currentUnit = sec_units[rand() % sec_units.size()];
			executeAction(ia(*currentUnit, first_army, sec_army), *currentUnit);
			first_army.purge();
		}		
	}

	return 0;
}

