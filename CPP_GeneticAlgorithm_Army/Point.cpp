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

std::ostream& operator<<(std::ostream& out, const Point &p)
{
    out<<"("<<p.x_get()<<","<<p.y_get()<<")";
    return out;
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