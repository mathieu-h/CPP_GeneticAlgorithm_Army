// CPP_GeneticAlgorithm_Army.cpp�: d�finit le point d'entr�e pour l'application console.
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
#include <iostream>

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
	std::locale::global(std::locale(""));
	int userAnswer = 1;
	while (userAnswer){
		std::srand(std::time(NULL));
		//Army first_army = Army(5, 100);
		//Army sec_army = Army(5, 100);
		//std::vector<int> scores = battleArmy(first_army, sec_army);
		//std::cout << "Le score de l'armee 1 est de : " << scores.at(0) << std::endl;
		//std::cout << "Le score de l'armee 2 est de : " << scores.at(1) << std::endl;
		std::cout << "------------------------------- NOUVEAU TOUR --------------------------------- : " << std::endl;
		bool goalReached = false;
		int nbArmies_N = 0;
		int numberOfUnits_X = 0;
		int levelUnits_Y = 0;
		int nbIteration_I = 0;
		// doit �tre inf�rieur a N-1 * nombre d'unit�s
		int scoreToReach_T = 0;
		std::cout << "Entrez le nombre d'arm�es qui vont se battre : " << std::endl;
		std::cin >> nbArmies_N;
		std::cout << "Entrez le nombre d'unit�s par arm�e : " << std::endl;
		std::cin >> numberOfUnits_X;
		std::cout << "Entrez le niveau global des unit�s d'une arm�e : " << std::endl;
		std::cin >> levelUnits_Y;
		std::cout << "Entrez le nombre d'it�ration de l'agorithme g�n�tique: " << std::endl;
		std::cin >> nbIteration_I;
		std::cout << "Entrez le score � atteindre pour l'arm�e � sauvegarder : " << std::endl;
		std::cin >> scoreToReach_T;

		std::vector<Army> armies = std::vector<Army>();
		for (int i = 0; i < nbArmies_N; ++i){
			armies.push_back(Army(numberOfUnits_X, levelUnits_Y));
		}

		for (int i = 0; i < nbIteration_I; ++i) {
			for (std::vector<Army>::iterator it = armies.begin(); it != armies.end(); ++it) {
				for (std::vector<Army>::iterator it_opp = it + 1; it_opp != armies.end(); ++it_opp){
					// appelle le constructeur par recopie
					Army first_army = *it;
					Army sec_army = *it_opp;
					if (sec_army.getId() == first_army.getId()){
						continue;
					}
					else {
						std::vector<int> scores = battleArmy(first_army, sec_army);
						it->setScore(it->getScore() + scores[0]);
						it_opp->setScore(it_opp->getScore() + scores[1]);
					}
				}
			}
			// On sort la liste d'arm�e
			std::sort(armies.begin(), armies.end());
			if (armies.at(0).getScore() > scoreToReach_T){
				goalReached = true;
				std::cout << "L'arm�e gagnante est : " << armies.at(0).getId() << ", son score est de : " << armies.at(0).getScore() << std::endl;
				break;
			}
			if (i < nbIteration_I-1){
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
			}
		}
		//first_army.saveArmy();
		if (!goalReached)
		{
			std::cout << "L'arm�e gagnante est : " << armies.at(0).getId() << ", son score est de : " << armies.at(0).getScore() << std::endl;
			std::cout << "Le score est trop haut, aucune arm�e n'a atteint le score que vous avez demand�e" << std::endl;
		}
		std::cout << "Entrez 1 pour continuer ou 0 pour arr�ter le programme : " << std::endl;
		std::cin >> userAnswer;
	}
	return 0;
}

