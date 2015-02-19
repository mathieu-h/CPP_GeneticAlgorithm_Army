#pragma once
#include "Action.h"
#include "Unit.h"

class ActionShoot
{
public:
	ActionShoot();
	~ActionShoot();

private:
	Unit* target;
};

