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
#include <algorithm>

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

std::vector<int> battleArmy(Army& first_army, Army& sec_army){
	IA ia = IA();
	first_army.setArmyInFormation(100);
	sec_army.setArmyInFormation(200);
	std::vector<Unit*> first_units = first_army.getUnitsList();
	std::vector<Unit*> sec_units = sec_army.getUnitsList();
	int tourCounter = 0;
	while (!first_army.isEmpty() && !sec_army.isEmpty()){
		++tourCounter;
		std::cout << "=============================== Tour " << tourCounter << " ===============================" << std::endl;
		Unit* currentUnit = nullptr;
		currentUnit = first_units[rand() % first_units.size()];
		executeAction(ia(*currentUnit, first_army, sec_army), *currentUnit, sec_army, A1);
		first_army.refreshUnits();
		sec_army.purge();
		currentUnit = sec_units[rand() % sec_units.size()];
		executeAction(ia(*currentUnit, sec_army, first_army), *currentUnit, first_army, A2);
		sec_army.refreshUnits();
		first_army.purge();
		std::cout << "" << std::endl;
	}
	std::cout << "Le score de l'armee 1 est de : " << first_army.size() << std::endl;
	//std::cout << "Le score de l'armee 2 est de : " << sec_army.size() << std::endl;
	std::vector<int> scores = std::vector<int>();
	scores.push_back(first_army.size());
	scores.push_back(sec_army.size());
	return scores;
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::srand(std::time(NULL));
	Army first_army = Army(5, 100);
	Army sec_army = Army(5, 100);
	std::vector<int> scores = battleArmy(first_army, sec_army);
	//std::cout << "Le score de l'armee 1 est de : " << scores.at(0) << std::endl;
	//std::cout << "Le score de l'armee 2 est de : " << scores.at(1) << std::endl;

	int nbArmies_N = 3;
	int numberOfUnits_X = 5;
	int levelUnits_Y = 100;
	int nbIteration_I = 10;
	std::vector<Army> armies = std::vector<Army>();
	for (int i = 0; i < nbArmies_N; ++i){
		armies.push_back(Army(numberOfUnits_X, levelUnits_Y));
	}

	for (int i = 0; i < nbIteration_I; ++i) {
		for (std::vector<Army>::iterator it = armies.begin(); it != armies.end(); ++it) {
			for (std::vector<Army>::iterator it_opp = armies.begin(); it != armies.end(); ++it){
				// copy it, copy it_opp
				//make it fight against it_opp
				// how to resolve the fact that it mustnt fight against itself ? (std::remove, id on army)
			}
		}
		std::sort(armies.begin(), armies.end());

	}

	getchar();
	return 0;
}

