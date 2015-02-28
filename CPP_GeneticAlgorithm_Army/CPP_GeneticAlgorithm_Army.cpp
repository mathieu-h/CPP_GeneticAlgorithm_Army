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
#define A1 1
#define A2 2

void executeAction(Action& action, Unit& currentUnit,Army& army, int currentArmy){
	if (action.getType() == MOVE){
		Point nextPosition = static_cast<ActionMove&>(action).getNextPosition();
		currentUnit.setPosition(nextPosition);
		std::cout << "Unite " << currentUnit.getId() << " (Armee" << currentArmy << ") bouge en position (" << (int)nextPosition.x_get() << "," << (int)nextPosition.y_get() << ")"<< std::endl;
	}
	else if (action.getType() == SHOOT && currentUnit.shoot()){
		int opponentArmy = 0;
		currentArmy == A1 ? opponentArmy = A2 : opponentArmy = A1;
		int targetID = static_cast<ActionShoot&>(action).getUnitID();
		Unit* target = army.getUnit(targetID);
		if (target == nullptr){
			getchar();
		}
		target->takeDamage(currentUnit.getDamage().getValue());
		//std::cout << "Shoot" << std::endl;
		std::cout << "Unite " << currentUnit.getId() << " (Armee" << currentArmy << ") tire sur l'Unite " << target->getId() << "(Armee" << opponentArmy << ") qui n'a plus que " 
			<< target->getHealth().getValue() << "PV" << std::endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::srand(std::time(NULL));
	Army first_army = Army(1, 100);
	Army sec_army = Army(1, 100);
	first_army.setArmyInFormation(100);
	sec_army.setArmyInFormation(200);
	std::vector<Unit*> first_units = first_army.getUnitsList();
	std::vector<Unit*> sec_units = sec_army.getUnitsList();
	IA ia = IA();
	int tourCounter = 0;

	while (!first_army.isEmpty() && !sec_army.isEmpty()){
		++tourCounter;
		std::cout << "=============================== Tour " << tourCounter << " ===================================" << std::endl;
		Unit* currentUnit = nullptr;
		//if (rand()%2)
		//{
		currentUnit = first_units[rand() % first_units.size()];
		executeAction(ia(*currentUnit, first_army, sec_army), *currentUnit, sec_army,A1);
		first_army.refreshUnits();
		sec_army.purge();
		//}
		//else
		//{
		currentUnit = sec_units[rand() % sec_units.size()];
		executeAction(ia(*currentUnit, sec_army, first_army), *currentUnit, first_army,A2);
		sec_army.refreshUnits();
		first_army.purge();
		//}
		std::cout << "" << std::endl;
	}

	getchar();
	return 0;
}

