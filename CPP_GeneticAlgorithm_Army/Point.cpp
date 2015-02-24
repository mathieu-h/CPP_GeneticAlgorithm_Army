#include "stdafx.h"
#include "Point.h"

Point::Point()
{
    this->x_ = 0.0f;
    this->y_ = 0.0f;
}

Point::Point(float x, float y)
{
    this->x_ = x;
    this->y_ = y;
}

Point::Point(const Point &p)
{
    this->x_ = p.x_;
    this->y_ = p.y_;
}

Point* Point::moveToPoint(Point& pointTarget, double speed)
{	
	double coeffMove = speed / this->distance(pointTarget);
	// if the speed is greater that the distance then we limit the coeff otherwise the unit will go too far
	if (coeffMove > 1) coeffMove = 1;
	coeffMove = 1-(speed / this->distance(pointTarget));
	float x = (1-coeffMove)*x_ + coeffMove * pointTarget.x_;
	float y = (1-coeffMove)*y_ + coeffMove * pointTarget.y_;
	return new Point(x, y);
}

Point* Point::moveAwayFromPoint(Point& pointTarget, double speed)
{
	double coeffMove = 1 + (speed / this->distance(pointTarget));
	float x = (1 - coeffMove)*x_ + coeffMove * pointTarget.x_;
	float y = (1 - coeffMove)*y_ + coeffMove * pointTarget.y_;
	return new Point(x, y);
}

std::ostream& operator<<(std::ostream& out, const Point &p)
{
    out<<"("<<p.x_get()<<","<<p.y_get()<<")";
    return out;
}

void Point::add(const Point& point){
	this->x_set(this->x_get()*point.x_get());
	this->y_set(this->y_get()*point.y_get());
}

Point& Point::operator+=(const Point& p){
	this->add(p);
	return *this;
}
Point Point::operator+(const Point& p) const{
	Point res = *this;
	res += p;
	return res;
}

Point& Point::operator-=(const Point& p){
	return this->operator+=(-p);
}

Point Point::operator-(const Point& p) const{
	return this->operator+(-p);
}

Point& Point::operator/=(float divider){
	this->x_set(x_/divider);
	this->x_set(y_ /divider);
	return *this;
}

Point Point::operator/(float divider) const{
	Point res = *this;
	return res/=(divider);
}

Point Point::operator-()const{
	return Point(-this->x_, -this->y_);
}

double Point::distance(const Point &P) const
{
    double dx = this->x_ - P.x_;
    double dy = this->y_ - P.y_;
    return sqrt(dx*dx + dy*dy); 
}

float Point::x_get() const
{
    return this->x_;
}

void Point::x_set(float x)
{
    this->x_ = x;
}

float Point::y_get() const
{
    return this->y_;
}

void Point::y_set(float y)
{
    this->y_ = y;
}

Point::~Point(void)
{
    
}

/*
Point operator+(const Point &p1, const Point &p2)
{
Point copy = Point(p1);
copy += p1;
return copy;
}
Point& operator+=(Point &p1, const Point &p2)
{
p1.add(p2);
return p1;
}

Point operator-(const Point &p1, const Point &p2)
{
return Point(p1.x_get() - p2.x_get(), p2.y_get() - p2.y_get());
}
*/