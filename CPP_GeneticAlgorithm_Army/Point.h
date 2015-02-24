#pragma once
#include <stdio.h>
#include <iostream>
#include <cmath>

class Point
{
private:
    float x_;
    float y_;
    
public:
	Point();
    Point(float x, float y);
    Point(const Point &p);
    ~Point(void);
    
	void add(const Point& point);
    void scale(float scale);
    float x_get() const;
    void x_set(float x);
    float y_get() const;
    void y_set(float y);

	Point* moveToPoint(Point& pointTarget, double speed);
	Point* moveAwayFromPoint(Point& pointTarget, double speed);
	void add(Point& point);

	Point operator-()const;
	Point operator-(const Point &p2) const;
	Point& operator-=(const Point& p);
	Point operator+(const Point &p2) const;
	Point& operator+=(const Point& p);
	Point& operator/=(float divider);
	Point operator/(float divider) const;

	double distance(const Point &P) const;
    
};
/*
Point operator+(const Point &p1, const Point &p2);
Point& operator+=(const Point &p1, const Point &p2);*/
std::ostream& operator<<(std::ostream& out, const Point &p);


