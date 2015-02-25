#pragma once
#include "stdafx.h"
#include "Army.h"
#include "Unit.h"
#include "Capacity.h"
#include "Action.h"
#include "ActionMove.h"
#include "ActionShoot.h"
#include <string>


class IA
{
public:
	IA(){};
	//IA(Unit* unit, Army armyOne, Army armyTwo) : _unit(unit), _armyOne(_armyOne), _armyTwo(_armyTwo) {};
	//IA() : _aiCode(LD){}
	//IA(IACode aiCode) : _aiCode(aiCode){}
	~IA();

	Action& operator() (Unit& unit, Army& armyOne, Army& armyTwo);
	Unit& chooseTarget(Unit& unit, Army& armyOpponent);

private:
	/*
	Unit* _unit;
	Army _armyOne;
	Army _armyTwo;
	*/
	//IACode _aiCode;
};

