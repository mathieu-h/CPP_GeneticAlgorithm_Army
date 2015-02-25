#include "stdafx.h"
#include "Army.h"
#include "Unit.h"
#include "Capacity.h"

Army::Army(int numberOfUnits, int level){
	for (int i = 0; i < numberOfUnits; ++i){
		Unit* newUnit = new Unit(level);
		_unitList.push_back(newUnit);
	}
}

// Vérifier si on peut bien passer ca par référence
Army::Army(std::vector<Unit*>& unitList){
	_unitList = unitList;
}

Unit& Army::getNearestUnit(const Point& p) {
	Unit* currentUnit;
	Unit* currentNearestUnit = new Unit(10);
	// I set the nearestUnit at the given position so i'm sure it's the closest possible
	currentNearestUnit->setPosition(Point(p));
	for (std::vector<Unit*>::iterator it = _unitList.begin(); it != _unitList.end(); ++it) {
		currentUnit = *it;
		if (currentUnit->getPosition().distance(p) < currentNearestUnit->getPosition().distance(p)){
			currentNearestUnit = currentUnit;
		}
	}
	return *currentNearestUnit;
}

Unit& Army::getFurthestUnit(const Point& p) {
	Unit* currentUnit;
	Unit* currentFurthestUnit = new Unit(10);	
	// I assume p(999,999) is pretty far
	currentFurthestUnit->setPosition(Point(999,999));
	for (std::vector<Unit*>::iterator it = _unitList.begin(); it != _unitList.end(); ++it) {
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
	for (std::vector<Unit*>::iterator it = _unitList.begin(); it != _unitList.end(); ++it) {
		currentUnit = *it;
		if (!currentUnit->isAlive()){
			_unitList.erase(it);
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
