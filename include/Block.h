#ifndef BLOCK_H
#define BLOCK_H

#include <Point.h>

class Block
{
public:
    Block();
    Block(Point position,double width,double height);
    ~Block();

    void Setcenter(Point val) { center = val; }
    void Setwidth(double val) { width = val; }
    void Setheight(double val) { height = val; }


    Point Getcenter() { return center; }
    double Getwidth() { return width; }
    double Getheight() { return height; }


    void Move(double x,double y);
    Point Vertices(int index);
    bool IsInside(Point p);

private:
    Point center;
    double width;
    double height;
};

#endif // BLOCK_H
