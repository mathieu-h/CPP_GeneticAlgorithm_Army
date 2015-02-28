#include "stdafx.h"
#include "Army.h"
#include "Unit.h"
#include "Capacity.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

Army::Army(int numberOfUnits, int level){
	for (int i = 0; i < numberOfUnits; ++i){
		Unit* newUnit = new Unit(level);
		_unitList.push_back(newUnit);
	}
	//_score = _unitList.size();
	_id = ++_idCounter;
	_score = 0;
}

// Vérifier si on peut bien passer ca par référence
Army::Army(std::vector<Unit*>& unitList){
	_unitList = unitList;
	//_score = _unitList.size();
	_id = ++_idCounter;
	_score = 0;
}

Army::Army(const Army& armyToCopy){
	_id = armyToCopy.getId();
	Unit* current;
	//std::copy(armyToCopy._unitList.begin(), armyToCopy._unitList.begin(), _unitList.begin());
	for (std::vector<Unit*>::const_iterator it = armyToCopy._unitList.begin(); it != armyToCopy._unitList.end(); ++it) {
		current = *it;
		_unitList.push_back(new Unit(*current));
	}
	_score = armyToCopy._score;
}

Unit& Army::getNearestUnit(const Point& p) const{
	Unit* currentUnit;
	Unit* currentNearestUnit = nullptr;
	for (std::vector<Unit*>::const_iterator it = _unitList.begin(); it != _unitList.end(); ++it) {
		if (currentNearestUnit == nullptr) currentNearestUnit = *it;
		currentUnit = *it;
		if (currentUnit->getPosition().distance(p) < currentNearestUnit->getPosition().distance(p)){
			currentNearestUnit = currentUnit;
		}
	}
	return *currentNearestUnit;
}

Unit& Army::getFurthestUnit(const Point& p) const{
	Unit* currentUnit;
	Unit* currentFurthestUnit = nullptr;
	for (std::vector<Unit*>::const_iterator it = _unitList.begin(); it != _unitList.end(); ++it) {
		if (currentFurthestUnit == nullptr) currentFurthestUnit = *it;
		currentUnit = *it;
		if (currentUnit->getPosition().distance(p) > currentFurthestUnit->getPosition().distance(p)){
			currentFurthestUnit = currentUnit;
		}
	}
	return *currentFurthestUnit;
}

Unit& Army::getLowestUnit(int capa_index) const{
	Unit* currentUnit;
	Unit* currentLowestUnit = new Unit(1000);
	for (std::vector<Unit*>::const_iterator it = _unitList.begin(); it != _unitList.end(); ++it) {
		currentUnit = (*it);
		if ((*currentUnit)[capa_index].getCLevel() < (*currentLowestUnit)[capa_index].getCLevel()){
			currentLowestUnit = currentUnit;
		}
	}
	return *currentLowestUnit;
}

Unit& Army::getHighestUnit(int capa_index) const{
	Unit* currentUnit;
	Unit* currentBestUnit = new Unit(0);
	for (std::vector<Unit*>::const_iterator it = _unitList.begin(); it != _unitList.end(); ++it) {
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

void  Army::saveArmy(){

	std::ofstream myfile;
	std::stringstream ss;
	ss << "army_" << this->getUnitsList().size() << "_" << this->getGlobalLevel() << ".save";
	std::string name = ss.str();
	myfile.open(name);
	myfile << *this;
	myfile.close();
		
}

void Army::mutate(){

	int randIndex = std::rand() % _unitList.size();
	_unitList.at(randIndex) = new Unit(_unitList.at(randIndex)->getLevel());
}

Army* Army::operator*(Army& army){

	int unitsCount = army.getUnitsList().size();
	std::vector<Unit*> newUnits = std::vector<Unit*>(unitsCount);

	int bla = unitsCount / 3;

	for (int i = 0; i < bla; ++i){
		newUnits.push_back(_unitList.at(i));
	}
	for (int i = 0; i < bla; ++i){
		newUnits.push_back(army._unitList.at(i));
	}

	unitsCount -= (2 * bla);

	for (int i = 0; i < bla; ++i){
		Unit* unitA = army._unitList.at(i);
		Unit* unitB = _unitList.at(i);
		newUnits.push_back(*unitA * *unitB);
	}

	return new Army(newUnits);
}

int Army::getGlobalLevel() const{
	Unit* currentUnit;
	int globalLevel = 0;
	for (std::vector<Unit*>::const_iterator it = _unitList.begin(); it != _unitList.end(); ++it) {
		currentUnit = *it;
		globalLevel += currentUnit->getLevel();
	}
	return globalLevel;
}

std::ostream& operator<<(std::ostream& out, const Army& army){
	std::vector<Unit*> unitList = army.getUnitsList();
	Unit* currentUnit;
	for (std::vector<Unit*>::const_iterator it = unitList.begin(); it != unitList.end(); ++it) {
		currentUnit = *it;
		out << *currentUnit << std::endl;
	}
	return out;
}