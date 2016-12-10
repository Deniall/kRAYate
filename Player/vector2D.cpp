#include "vector2D.h"
#include <iostream>

using namespace std;

Vector2D::Vector2D(int ix,int iy){
    x = (double)ix;
    y = (double)iy;
}

Vector2D::Vector2D(double ix,double iy)
{
    x = ix;
    y = iy;
};

Vector2D::Vector2D(){
    x = 0;
    y = 0;
};

Vector2D Vector2D::normalized()
{
    double m = magnitude();
    Vector2D z(0,0);
    z.x = x/m;
    z.y = y/m;
    return z;
}

double Vector2D::magnitude()
{
    Vector2D z(0,0);
    return distance(z);
}

double Vector2D::distance(Vector2D point)
{
    return(sqrt(pow(x-point.x,2)+pow(y-point.y,2)));
}

Vector2D Vector2D::clampMagnitude(double max)
{
    Vector2D m(x,y);
    m = m.normalized();
    m.x = m.x*max;
    m.y = m.y*max;
    return m;
}

Vector2D Vector2D::lerp(Vector2D to, double amount)
{
    double xMove = (to.x - x)*amount;
    double yMove = (to.y - y)*amount;
    Vector2D z(0,0);
    z.x = x+xMove;
    z.y = y+yMove;
    if(z.x != to.x)
    {
        if(abs(z.x - to.x)/(z.x - to.x) != abs(x - to.x)/(x - to.x))
        {
            z.x = to.x;
        }
    }
    if(z.y != to.y)
    {
        if(abs(z.y - to.y)/(z.y - to.y) != abs(y - to.y)/(y - to.y))
        {
            z.y = to.y;
        }
    }
    return z;
}



