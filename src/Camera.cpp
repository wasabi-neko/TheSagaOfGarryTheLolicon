#include "Camera.h"

#include <Point.h>
#include <Block.h>

Camera::Camera()
{
    //ctor
}

Camera::Camera(Block visible_area)
{
    this->visible_area = visible_area;
}

Camera::~Camera()
{
    //dtor
}

void Camera::MoveTo(Point destination)
{
    visible_area.Setcenter( destination);
}
