#pragma once
#include "Unit.h"
#include "stdafx.h"
#include <vector>

class Army
{
public:
	Army();
	~Army();

	std::vector<Unit*> getUnitsList();
private:
	std::vector<Unit*> unitList;
};

