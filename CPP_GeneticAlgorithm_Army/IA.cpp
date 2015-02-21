#include "stdafx.h"
#include "IA.h"




IA::~IA()
{
}

Action IA::operator() (Unit* unit, Army armyOne, Army armyTwo){
	// teste si l'unit courante peut tirer
	if (unit->shoot()){
	// si oui, choisir sa cible en fonction du code ia
		Unit* enemy = chooseTarget(armyTwo);
		// si la cible est à portée => tirer desssus
		if (enemy->getPosition().distance(unit->getPosition()) < unit->getRange().getValue()){
			enemy->takeDamage(unit->getDamage().getValue());
		}
		// si non, se rapprocher d'elle ( en fonction de sa speed ?)
	}
	// si non aller dans la direction opposée au centre des ennemis ou de l'ennemi le + proche (à voir)	
	else
	{

	}
}

