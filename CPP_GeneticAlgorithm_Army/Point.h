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
    
    void add(const Point &p);
    void scale(float scale);
    float x_get() const;
    void x_set(float x);
    float y_get() const;
    void y_set(float y);
    
};

std::ostream& operator<<(std::ostream& out, const Point &p);


