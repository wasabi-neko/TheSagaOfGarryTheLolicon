#include "Block.h"
#include <Point.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <cmath>

Block::Block()
{
    //ctor
}

Block::Block(Point position, double width, double height)
{
    this->center = position;
    this->width = width;
    this->height = height;
}

Block::~Block()
{
    //dtor
}

void Block::Move(double x, double y)
{
    center.Addx(x);
    center.Addy(y);
}

Point Block::Vertices(int index)
{
    /** \brief point0(0,0) , point1(1,0) , point2(1,1) , point3(0,1)
     *
     * \param index: the index of vertices
     * \return
     *
     */

     Point temp;

    switch(index)
    {
    case 0:

        temp.Setx( center.Getx() - width/2 );
        temp.Sety( center.Gety() - height/2 );
        break;
    case 1:

        temp.Setx( center.Getx() + width/2 );
        temp.Sety( center.Gety() - height/2 );
        break;
    case 2:

        temp.Setx( center.Getx() + width/2 );
        temp.Sety( center.Gety() + height/2 );
        break;
    case 3:

        temp.Setx( center.Getx() - width/2 );
        temp.Sety( center.Gety() + height/2 );
        break;
    default:

        printf("fuck Block\n");
        system("pause");
        exit(-1);

    }

    return temp;
}

bool Block::IsInside(Point p)
{
    bool x_inside , y_inside;

    x_inside =  width > std::abs(p.Getx()-center.Getx());
    y_inside = height > std::abs(p.Gety()-center.Gety());

    return x_inside&&y_inside;
}





















