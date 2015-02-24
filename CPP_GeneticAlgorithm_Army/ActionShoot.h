#pragma once
#include "Action.h"
#include "Unit.h"

class ActionShoot : public Action
{
public:
	ActionShoot(Unit* target) :	_target(target) {
		_type = "Shoot";
	};
	~ActionShoot();

private:
	Unit* _target;
};

