#include "stdafx.h"
#include "IA.h"
#include "Action.h"


IA::~IA()
{
}

Action& IA::operator() (Unit& unit, Army& armyOne, Army& armyTwo){
	// teste si l'unit courante peut tirer
	if (unit.canShoot()){
		// si oui, choisir sa cible en fonction du code ia
		Unit enemy = chooseTarget(unit, armyTwo);
		// si la cible est à portée => tirer desssus		
		if (enemy.getPosition().distance(unit.getPosition()) < unit.getRange().getValue()){
			//enemy.takeDamage(unit.getDamage().getValue());
			return *new ActionShoot(enemy);
		}

		// si non, se rapprocher d'elle ( en fonction de sa speed ?)
		else
		{
			Point* newPosition = unit.getPosition().moveToPoint(enemy.getPosition(), unit.getSpeed().getValue());
			//unit.setPosition(*newPosition);
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
		Point* newPosition = unit.getPosition().moveAwayFromPoint(centerOfArmy, unit.getSpeed().getValue());
		//unit.setPosition(*newPosition);
		return *new ActionMove(*newPosition);
	}
}

Unit& IA::chooseTarget(Unit& unit, Army& armyOpponent){
	switch (unit.getIACode()){
	case LD:
		return armyOpponent.getNearestUnit(unit.getPosition());
	case HD:
		return armyOpponent.getFurthestUnit(unit.getPosition());
	case L0:
		return armyOpponent.getLowestUnit(0);
	case H0:
		return armyOpponent.getHighestUnit(0);
	case L1:
		return armyOpponent.getLowestUnit(1);
	case H1:
		return armyOpponent.getHighestUnit(1);
	case L2:
		return armyOpponent.getLowestUnit(2);
	case H2:
		return armyOpponent.getHighestUnit(2);
	case L3:
		return armyOpponent.getLowestUnit(3);
	case H3:
		return armyOpponent.getHighestUnit(3);
	case L4:
		return armyOpponent.getLowestUnit(4);
	case H4:
		return armyOpponent.getHighestUnit(4);
	case L5:
		return armyOpponent.getLowestUnit(5);
	case H5:
		return armyOpponent.getHighestUnit(5);
	case L6:
		return armyOpponent.getLowestUnit(6);
	case H6:
		return armyOpponent.getHighestUnit(6);
	default:
		return armyOpponent.getNearestUnit(unit.getPosition());
	}
}



