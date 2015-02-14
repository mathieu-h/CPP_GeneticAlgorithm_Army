#pragma once
class Capacity
{
public:
	Capacity(float value) : _value(value), _level(0){}

	// if we don't set this virtual 
	virtual ~Capacity();

	virtual float getValue() const = 0;
	
	int getLevel() const
	{
		return _level;
	}

	void upgrade(){
		_level += 1;
	}

	void downgrade(){
		_level -= 1;
	}

private:
	float _value;
	int _level;
};

