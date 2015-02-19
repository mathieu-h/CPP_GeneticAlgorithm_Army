#pragma once
#include <string>

class Action
{
public:
	Action();
	~Action();

	std::string getType() const { return _type; }

protected:
	std::string _type;
};

