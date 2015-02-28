#include "stdafx.h"
#include "Army.h"
#include "Unit.h"
#include "Capacity.h"
#include <vector>
#include <algorithm>

Army::Army(int numberOfUnits, int level){
	for (int i = 0; i < numberOfUnits; ++i){
		Unit* newUnit = new Unit(level);
		_unitList.push_back(newUnit);
	}
}

// V�rifier si on peut bien passer ca par r�f�rence
Army::Army(std::vector<Unit*>& unitList){
	_unitList = unitList;
}

Unit& Army::getNearestUnit(const Point& p) {
	Unit* currentUnit;
	Unit* currentNearestUnit = nullptr;
	for (std::vector<Unit*>::iterator it = _unitList.begin(); it != _unitList.end(); ++it) {
		if (currentNearestUnit == nullptr) currentNearestUnit = *it;
		currentUnit = *it;
		if (currentUnit->getPosition().distance(p) < currentNearestUnit->getPosition().distance(p)){
			currentNearestUnit = currentUnit;
		}
	}
	return *currentNearestUnit;
}

Unit& Army::getFurthestUnit(const Point& p) {
	Unit* currentUnit;
	Unit* currentFurthestUnit = nullptr;
	for (std::vector<Unit*>::iterator it = _unitList.begin(); it != _unitList.end(); ++it) {
		if (currentFurthestUnit == nullptr) currentFurthestUnit = *it;
		currentUnit = *it;
		if (currentUnit->getPosition().distance(p) > currentFurthestUnit->getPosition().distance(p)){
			currentFurthestUnit = currentUnit;
		}
	}
	return *currentFurthestUnit;
}

Unit& Army::getLowestUnit(int capa_index) {
	Unit* currentUnit;
	Unit* currentLowestUnit = new Unit(1000);
	for (std::vector<Unit*>::iterator it = _unitList.begin(); it != _unitList.end(); ++it) {
		currentUnit = (*it);
		if ((*currentUnit)[capa_index].getCLevel() < (*currentLowestUnit)[capa_index].getCLevel()){
			currentLowestUnit = currentUnit;
		}
	}
	return *currentLowestUnit;
}

Unit& Army::getHighestUnit(int capa_index){
	Unit* currentUnit;
	Unit* currentBestUnit = new Unit(0);
	for (std::vector<Unit*>::iterator it = _unitList.begin(); it != _unitList.end(); ++it) {
		currentUnit = (*it);
		if ((*currentUnit)[capa_index].getCLevel() > (*currentBestUnit)[capa_index].getCLevel()){
			currentBestUnit = currentUnit;
		}
	}
	return *currentBestUnit;
}

void Army::purge(){
	Unit* currentUnit;
	std::vector<Unit*> copy = _unitList;
	for (std::vector<Unit*>::iterator it = copy.begin(); it != copy.end(); ++it) {
		currentUnit = *it;
		if (!currentUnit->isAlive()){
			_unitList.erase(std::remove(_unitList.begin(), _unitList.end(), *it), _unitList.end());
		}
		else
		{
			currentUnit->refresh();
		}
	}
}

void Army::refreshUnits(){
	Unit* currentUnit;
	for (std::vector<Unit*>::iterator it = _unitList.begin(); it != _unitList.end(); ++it) {
		currentUnit = *it;
		currentUnit->refresh();
	}
}


void Army::setArmyInFormation(float verticalOrigin){
	float horizontalOrigin = 0;
	Unit* currentUnit;
	for (std::vector<Unit*>::iterator it = _unitList.begin(); it != _unitList.end(); ++it) {
		currentUnit = *it;
		currentUnit->setPosition(Point(horizontalOrigin, verticalOrigin));
		horizontalOrigin += 10;
	}
}

Army::~Army()
{
}
