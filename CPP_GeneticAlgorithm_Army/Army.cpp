#include "stdafx.h"
#include "Army.h"
#include "Unit.h"
#include "Capacity.h"

Army::Army(int numberOfUnits, int level){
	for (int i = 0; i < numberOfUnits; ++i){
		_unitList.push_back(new Unit(level));
	}
}

// Vérifier si on peut bien passer ca par référence
Army::Army(std::vector<Unit*>& unitList){
	_unitList = unitList;
}

Unit& Army::getNearestUnit(const Point& p){
	Unit* currentUnit;
	Unit* currentNearestUnit = new Unit(1000);
	for (std::vector<Unit*>::iterator it = _unitList.begin(); it != _unitList.end(); ++it) {
		currentUnit = *it;
		if (currentUnit->getPosition().distance(p) < currentNearestUnit->getPosition().distance(p)){
			currentNearestUnit = currentUnit;
		}
	}
	return *currentNearestUnit;
}

Unit& Army::getFurtherUnit(const Point& p){
	Unit* currentUnit;
	Unit* currentFurthestUnit = new Unit(1000);
	for (std::vector<Unit*>::iterator it = _unitList.begin(); it != _unitList.end(); ++it) {
		currentUnit = *it;
		if (currentUnit->getPosition().distance(p) > currentFurthestUnit->getPosition().distance(p)){
			currentFurthestUnit = currentUnit;
		}
	}
	return *currentFurthestUnit;
}

Unit& Army::getLowestUnit(int capa_index){
	Unit* currentUnit;
	Unit* currentLowestUnit = new Unit(1000);
	for (std::vector<Unit*>::iterator it = _unitList.begin(); it != _unitList.end(); ++it) {
		currentUnit = *it;
		if (currentUnit[capa_index].getLevel() < currentLowestUnit[capa_index].getLevel()){
			currentLowestUnit = currentUnit;
		}
	}
	return *currentLowestUnit;
}

Unit& Army::getHighestUnit(int capa_index){
	Unit* currentUnit;
	Unit* currentBestUnit = new Unit(0);
	for (std::vector<Unit*>::iterator it = _unitList.begin(); it != _unitList.end(); ++it) {
		currentUnit = *it;
		if (currentUnit[capa_index].getLevel() > currentBestUnit[capa_index].getLevel()){
			currentBestUnit = currentUnit;
		}
	}
	return *currentBestUnit;
}

void Army::purge(){
	Unit* currentUnit;
	for (std::vector<Unit*>::iterator it = _unitList.begin(); it != _unitList.end(); ++it) {
		currentUnit = *it;
		if (currentUnit->getHealth().getValue() <= 0){
			_unitList.erase(it);
		}
	}
}

Army::~Army()
{
}
