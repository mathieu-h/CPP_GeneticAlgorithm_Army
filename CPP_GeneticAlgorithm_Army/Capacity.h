#pragma once
class Capacity
{
public:
	Capacity() : _level(0){}

	// if we don't set this virtual, could have problems when an instance of a subclass object is 
	// destructed since you don't know which destroyer you should call
	virtual ~Capacity();

	// const is useless here actually since it's a float
	// virtual const float getValue() = 0;
	
	int getLevel() const
	{
		return _level;
	}

	float getValue() const{
		return _value;
	}

	virtual void updateValue() = 0;

	void upgrade(){
		_level += 1;
		updateValue();
	}

	void downgrade(){
		_level -= 1;
		updateValue();
	}
protected:
	int _level;
	float _value;
};

