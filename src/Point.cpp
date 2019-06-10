
#include "Point.h"
#include <stdio.h>
#include <cmath>
#include <math.h>

#define PI 3.1415926535897932384626433832

Point::Point()
{
    //ctor
}

Point::Point(double setx, double sety)
{
    this->x = setx;
    this->y = sety;
}

Point::~Point()
{
    //dtor
}

double Point::DistantTo(Point p)
{
    return sqrt( pow( x-p.Getx() ,2) + pow( y-p.Gety() ,2) );
}

double Point::ThetaTo(Point p)
{
    double distant;
    double theta;


    distant = this->DistantTo( p );

    theta = asin( (p.Gety()-y) / distant );

    if( (p.Getx()-x) < 0 )
    {
        theta = PI - theta;
    }
    else if( (p.Getx()-x)>=0 && (p.Gety()-y) < 0 )
    {
        theta = (2*PI) + theta;
    }

    return theta;
}

Point Point::operator+(Point& point)
{
    Point temp;

    temp.Setx( this->x + point.Getx() );
    temp.Sety( this->y + point.Gety() );


    return temp;
}

Point Point::operator-(Point &point)
{
    Point temp( x-point.Getx(), y-point.Gety());
    return temp;
}

Point Point::operator*(const double& param)
{
    Point temp;

    temp.Setx( this->x * param);
    temp.Sety( this->y * param);

    return temp;
}

Point Point::operator/(const double& param)
{
    Point temp;

    temp.Setx( this->x / param);
    temp.Sety( this->y / param);

    return temp;
}


bool Point::operator==(Point& point)
{
    bool bx = std::abs( this->x - point.Getx() ) <= 0.0001;
    bool by = std::abs( this->y - point.Gety() ) <= 0.0001;


    return bx&&by;
}





