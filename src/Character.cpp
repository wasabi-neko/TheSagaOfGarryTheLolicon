
#include "Character.h"

#include <Point.h>
#include <Block.h>
#include <Camera.h>
#include  <Image.h>

#include <math.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

Character::Character()
{
    //ctor
}

Character::Character(Point location,int  width, int height, Image* skin, double speed, double gravity, int max_health_point, int attack_value)
{
    Block temp(location,width,height);
    this->character_block = temp;

    free(&temp);

    this->skin = skin;
    this->speed =speed;
    this->gravity = gravity;
    this->max_health_point = max_health_point;
    this->health_point = max_health_point;
    this->attack_value = attack_value;
}

Character::~Character()
{
    //dtor

    free( skin);
}

bool Character::IsDead(void)
{
    return health_point <= 0;
}

void Character::MoveL(double val )
{
    Point p;

    p = character_block.Getcenter();
    p.Addx( -val );
    character_block.Setcenter( p );
}

void Character::MoveR(double val)
{
    Point p;

    p = character_block.Getcenter();
    p.Addx( val );
    character_block.Setcenter( p );
}

void Character::MoveUp(double val )
{
    Point p;

    p = character_block.Getcenter();
    p.Addy( val );
    character_block.Setcenter( p );
}

void Character::MoveDown(double val)
{
    Point p;

    p = character_block.Getcenter();
    p.Addy( -val );
    character_block.Setcenter( p );
}

void Character::Show(Camera cam)
{
    Point position;
    Point cam_location = cam.Getlocation();
    Point skin_location = character_block.Getcenter() + skin_difference;

    position = skin_location - cam_location;    //相對於camera之位置

    position.Setx( position.Getx() / cam.Getwidth() *2 );
    position.Sety( position.Gety() / cam.Getheight() *2 );

    skin->GLDraw(position, cam.Getwidth(), cam.Getheight() );
}

void Character::AddHealthPoint(int value)
{
    if( !health_point_lock )
    {
        health_point += value;

        if( health_point > max_health_point )
            health_point = max_health_point;
    }
}







