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
int Army::_idCounter = 0;
/*
#define A1 1
#define A2 2
*/
void executeAction(Action& action, Unit& currentUnit,Army& army, int currentArmy, int opponentArmy){
	if (action.getType() == MOVE){
		Point nextPosition = static_cast<ActionMove&>(action).getNextPosition();
		currentUnit.setPosition(nextPosition);
		//std::cout << "Unite " << currentUnit.getId() << " (Armee" << currentArmy << ") bouge en position (" << (int)nextPosition.x_get() << "," << (int)nextPosition.y_get() << ")"<< std::endl;
	}
	else if (action.getType() == SHOOT && currentUnit.shoot()){
		int targetID = static_cast<ActionShoot&>(action).getUnitID();
		Unit* target = army.getUnit(targetID);
		target->takeDamage(currentUnit.getDamage().getValue());
		//std::cout << "Unite " << currentUnit.getId() << " (Armee" << currentArmy << ") tire sur l'Unite " << target->getId() << "(Armee" << opponentArmy << ") qui n'a plus que " 
		//	<< target->getHealth().getValue() << "PV" << std::endl;
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
		//std::cout << "=============================== Tour " << tourCounter << " ===============================" << std::endl;
		Unit* currentUnit = nullptr;
		currentUnit = first_units[rand() % first_units.size()];
		executeAction(ia(*currentUnit, first_army, sec_army), *currentUnit, sec_army, first_army.getId(), sec_army.getId());
		first_army.refreshUnits();
		sec_army.purge();
		currentUnit = sec_units[rand() % sec_units.size()];
		executeAction(ia(*currentUnit, sec_army, first_army), *currentUnit, first_army, sec_army.getId(), first_army.getId());
		sec_army.refreshUnits();
		first_army.purge();
		//std::cout << "" << std::endl;
	}
	std::cout << "Le score de l'armee " << first_army.getId() << " est de : " << first_army.size() << std::endl;
	std::cout << "Le score de l'armee " << sec_army.getId() << " est de : " << sec_army.size() << std::endl;
	std::cout << "----------------------------------------------------------------------" << std::endl;
	std::vector<int> scores = std::vector<int>();
	scores.push_back(first_army.size());
	scores.push_back(sec_army.size());
	return scores;
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::srand(std::time(NULL));
	//Army first_army = Army(5, 100);
	//Army sec_army = Army(5, 100);
	//std::vector<int> scores = battleArmy(first_army, sec_army);
	//std::cout << "Le score de l'armee 1 est de : " << scores.at(0) << std::endl;
	//std::cout << "Le score de l'armee 2 est de : " << scores.at(1) << std::endl;

	int nbArmies_N = 10;
	int numberOfUnits_X = 5;
	int levelUnits_Y = 100;
	int nbIteration_I = 1;
	// doit être inférieur a N-1 * nombre d'unités
	int scoreToReach_T = 39;
	
	std::vector<Army> armies = std::vector<Army>();
	for (int i = 0; i < nbArmies_N; ++i){
		armies.push_back(Army(numberOfUnits_X, levelUnits_Y));
	}
	
	for (int i = 0; i < nbIteration_I; ++i) {
		for (std::vector<Army>::iterator it = armies.begin(); it != armies.end(); ++it) {
			for (std::vector<Army>::iterator it_opp = it+1; it_opp != armies.end(); ++it_opp){
				// appelle le constructeur par recopie
				Army first_army = *it;
				Army sec_army = *it_opp;
				if (sec_army.getId() == first_army.getId()){ 
					continue; 
				} else { 
					std::vector<int> scores = battleArmy(first_army, sec_army);
					it->setScore(it->getScore() + scores[0]);
					it_opp->setScore(it_opp->getScore() + scores[1]);
				}
			}
		}
		// On sort la liste d'armée
		std::sort(armies.begin(), armies.end());
		if (armies.at(0).getScore() > scoreToReach_T){
			std::cout << "L'armée gagnante est : " << armies.at(0).getId() << ", son score est de : " << armies.at(0).getScore() << std::endl;
			break;
		}
		std::vector<Army> newArmies = std::vector<Army>();
		newArmies.insert(newArmies.begin(), armies.begin(), armies.begin() + nbArmies_N / 10);

		for (int j = 0; j < (nbArmies_N*0.3); j++){
			newArmies.push_back(armies[j].mutate());
			newArmies.push_back(*(armies[j] * armies[rand() % nbArmies_N]));
			newArmies.push_back(Army(numberOfUnits_X, levelUnits_Y));
		}
		for (int k = 0; k < newArmies.size(); ++k){
			newArmies.at(k).setScore(0);
		}
		armies = newArmies;
		/*
		On créé notre nouvelle génération d’armées(qui remplacera la génération courante) de la façon suivante :
				i.on garde les(N*0.1) meilleures armées
				ii.on prend un croisement issu de chacune des(N*0.3) meilleures armées avec une autre prise aléatoirement
				iii.on prend une mutation de chacune des(N*0.3) meilleures armées
				iv.on génère(N*0.3) nouvelles armées aléatoirement
		*/
	}
	//On save l'armée à l'indice 0 de armies
	//first_army.saveArmy();

	//std::cout << "L'armée gagnante est : " << armies.at(0).getId() << ", son score est de : " << armies.at(0).getScore() << std::endl;
	std::cout << "Try again" << std::endl;
	getchar();
	return 0;
}

