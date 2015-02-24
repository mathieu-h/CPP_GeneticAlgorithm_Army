#include "stdafx.h"
#include "IA.h"
#include "Action.h"


IA::~IA()
{
}

Action& IA::operator() (Unit* unit, Army armyOne, Army armyTwo){
	// teste si l'unit courante peut tirer
	if (unit->shoot()){
	// si oui, choisir sa cible en fonction du code ia
		Unit* enemy = chooseTarget(armyTwo);
		// si la cible est à portée => tirer desssus		
		if (enemy->getPosition().distance(unit->getPosition()) < unit->getRange().getValue()){
			//enemy->takeDamage(unit->getDamage().getValue());			
			return *new ActionShoot(enemy);
		}
		
		// si non, se rapprocher d'elle ( en fonction de sa speed ?)
		else
		{
			Point* newPosition = unit->getPosition().moveToPoint(enemy->getPosition(), unit->getSpeed().getValue());
			//unit->setPosition(*newPosition);
			return *new ActionMove(*newPosition);
		}
	}
	// si non aller dans la direction opposée au centre des ennemis ou de l'ennemi le + proche (à voir)	
	else
	{
		std::vector<Unit*> units = armyTwo.getUnitsList();
		Point centerOfArmy = Point();
		for (auto unit : units){
			centerOfArmy += unit->getPosition();
		}
		centerOfArmy /= static_cast<float> (units.size());
		Point* newPosition = unit->getPosition().moveToPoint(centerOfArmy, unit->getSpeed().getValue());
		//unit->setPosition(*newPosition);
		return *new ActionMove(*newPosition);
	}
}

Unit* IA::chooseTarget(Army armyOpponent) const{
	//
	return new Unit(10);
}



