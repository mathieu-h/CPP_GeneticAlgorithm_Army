#pragma once
#include "Unit.h"
#include "stdafx.h"
#include "Capacity.h"
#include <vector>


class Army
{
public:
	static int _idCounter;
	Army(int numberOfUnits, int level);
	Army(std::vector<Unit*>& unitList);
    Army::Army(const Army& armyToCopy);
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
	int getId() const{
		return _id;
	}

	int getScore() const{ 
		return _score;
	}

	void setScore(int newScore){
		_score = newScore;
	}

	bool isEmpty(){
		return _unitList.size() == 0;
	}


	void setArmyInFormation(float verticalOrigin);
	void purge();
	void refreshUnits();
	void saveArmy();
	void mutate();

	Army* operator*(Army& army);
	
private:
	std::vector<Unit*> _unitList;
	int _id;
	int _score;
};

inline bool operator<(const Army& army1, const Army& army2){
	if (army1.getScore() > army2.getScore()){
		return true;
	}
	else
	{
		return false;
	}
}
std::ostream& operator<<(std::ostream& out, const Army& army);
inline bool operator>(const Army& army1, const Army& army2){ return army2 < army1; }
inline bool operator<=(const Army& army1, const Army& army2){ return !(army1>army2); }
inline bool operator>=(const Army& army1, const Army& army2){ return !(army2>army1); }

inline bool operator==(const Army& sol1, const Army& sol2){
	if (sol1.getScore() == sol2.getScore()){
		return true;
	}
	return false;
}
inline bool operator!=(const Army& sol1, const Army& sol2){ return !(sol1 == sol2); }