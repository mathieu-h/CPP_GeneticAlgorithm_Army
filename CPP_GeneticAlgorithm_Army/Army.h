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

	Unit& getNearestUnit(const Point& p) const;
	Unit& getFurthestUnit(const Point& p) const;
	Unit& getLowestUnit(int capa_index) const;
	Unit& getHighestUnit(int capa_index) const;

	Unit* getUnit(int id){
		Unit* current;
		for (std::vector<Unit*>::iterator it = _unitList.begin(); it != _unitList.end(); ++it) {
			current = (*it);
			if ((*current).getId() == id){
				return current;
			}
		}
	}

	int getGlobalLevel() const;

	int size() const {
		return _unitList.size();
	}

	bool isEmpty(){
		return _unitList.size() == 0;
	}
	void setArmyInFormation(float verticalOrigin);
	void purge();
	void refreshUnits();
	void saveArmy();
private:
	std::vector<Unit*> _unitList;
};

