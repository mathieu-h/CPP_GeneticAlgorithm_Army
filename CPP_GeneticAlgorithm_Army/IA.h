#pragma once
#include "stdafx.h"
#include "Army.h"
#include "Unit.h"
#include "Capacity.h"
#include "Action.h"
#include <string>

class IA
{
public:
	//IA(Unit* unit, Army armyOne, Army armyTwo) : _unit(unit), _armyOne(_armyOne), _armyTwo(_armyTwo) {};
	IA(std::string aiCode) : _aiCode(aiCode){}
	~IA();

	Action operator() (Unit* unit, Army armyOne, Army armyTwo)
	{
		
	}

private:
	/*
	Unit* _unit;
	Army _armyOne;
	Army _armyTwo;
	*/
	std::string _aiCode;
};

