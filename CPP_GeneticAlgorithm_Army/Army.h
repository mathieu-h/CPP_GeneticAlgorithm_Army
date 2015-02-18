#pragma once
#include "Unit.h"
#include "stdafx.h"
#include "Capacity.h"
#include <vector>

class Army
{
public:
	Army(int numberOfUnits, int level);
	Army(std::vector<Unit*>& unitList);
	~Army();

	std::vector<Unit*> getUnitsList() const
	{
		return _unitList;
	}

	Unit& getNearestUnit(const Point& p);
	Unit& getFurtherUnit(const Point& p);
	Unit& getLowestUnit(int capa_index);
	Unit& getHighestUnit(int capa_index);


	int size() const {
		return _unitList.size();
	}

	void purge();
private:
	std::vector<Unit*> _unitList;
};

