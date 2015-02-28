#pragma once


enum IACode { LD = 0, HD, L0, H0, L1, H1, L2, H2, L3, H3, L4, H4, L5, H5, L6, H6 };

class Capacity
{

public:
	Capacity() : _level(0), _value(0){}

	// if we don't set this virtual, could have problems when an instance of a subclass object is 
	// destructed since you don't know which destroyer you should call
	virtual ~Capacity();

	int getCLevel() const
	{
		return _level;
	}

	float getValue() const{
		return _value;
	}

	// must be pure virtual since each child has it's own implementation
	virtual void updateValue() = 0;

	void upgrade(int level = 1){
		_level += level;
		updateValue();
	}

	void downgrade(int level = 1){
		_level -= level;
		updateValue();
	}

protected:
	int _level;
	float _value;
};

