#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>
#include <Point.h>
#include <Block.h>

class Camera
{
public:
    Camera();
    Camera(Block visible_area);
    ~Camera();

    Block Getvisible_area() { return visible_area; }
    Point Getlocation() { return visible_area.Getcenter(); }
    int Getwidth() { return round(visible_area.Getwidth() ); }
    int Getheight() { return round(visible_area.Getheight() ); }

    void Setvisible_area(Block val) { visible_area = val; }

    void MoveTo(Point destination);


private:
    Block visible_area;
};

#endif // CAMERA_H
