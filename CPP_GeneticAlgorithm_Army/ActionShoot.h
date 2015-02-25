#pragma once
#include "Action.h"
#include "Unit.h"

class ActionShoot : public Action
{
public:
	ActionShoot(Unit& target) : _target(target) {
		_type = SHOOT;
	};
	~ActionShoot();
	/*
	int getUnitID() const
	{
		return _target.getId();
	}
	*/
	Unit& getTarget() 
	{
		return _target;
	}

private:
	Unit _target;
};

