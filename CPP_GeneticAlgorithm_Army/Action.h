#pragma once
#include <string>

enum A_TYPE { MOVE, SHOOT };

class Action
{
public:
	Action();
	~Action();

	A_TYPE getType() const { return _type; }
protected:
	A_TYPE _type;
};

