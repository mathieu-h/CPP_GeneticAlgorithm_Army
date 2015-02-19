#pragma once
#include "Action.h"
#include "Unit.h"

class ActionShoot : Action
{
public:
	ActionShoot() {
		_type = "Shoot";
	};
	~ActionShoot();

private:
	Unit* target;
};

