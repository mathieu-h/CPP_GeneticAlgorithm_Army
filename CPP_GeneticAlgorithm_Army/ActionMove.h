#pragma once
#include "Action.h"
#include "Point.h"

class ActionMove : public Action
{
public:
	ActionMove(Point& nextPosition) : _nextPosition(nextPosition) {
		_type = MOVE;
	};

	~ActionMove();

	Point getNextPosition() const { return _nextPosition; }

private:
	Point _nextPosition;
};

