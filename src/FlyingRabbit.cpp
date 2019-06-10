#include "FlyingRabbit.h"

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <Point.h>
#include <Block.h>
#include <Player.h>

#define SPEED 400
#define MAX_HEALTH_POINT 10
#define ATTACK_VALUE 1

#define FREEZE_TIME 50 //0.001 sec

extern unsigned FPS;

long FlyingRabbit::freeze_clock = -FREEZE_TIME;

FlyingRabbit::FlyingRabbit()
{
    //ctor
    this->Setspeed( SPEED/(double)FPS );
    this->attack_value = ATTACK_VALUE;
    this->max_health_point = MAX_HEALTH_POINT;
    this->health_point = max_health_point;
    this->direction = 0;
    this->skin_difference = Point(0,0);
}

FlyingRabbit::~FlyingRabbit()
{
    //dtor
}

void FlyingRabbit::Prepare(void)
{
    normal_skin[0].ReadImg("rabbit_skin//normal0.png");
    normal_skin[1].ReadImg("rabbit_skin//normal1.png");
//    printf("rabbit normal_skin\n");

    battack_skin[0].ReadImg("rabbit_skin//battack0.png");
    battack_skin[1].ReadImg("rabbit_skin//battack1.png");
//    printf("rabbit battack_skin\n");


    normal_skin[0].UploadTexture();
    normal_skin[1].UploadTexture();
    battack_skin[0].UploadTexture();
    battack_skin[1].UploadTexture();

    normal_skin[0].ReleaseImg();
    normal_skin[1].ReleaseImg();
    battack_skin[0].ReleaseImg();
    battack_skin[1].ReleaseImg();

    skin = normal_skin+1;
    freezing = false;
}

void FlyingRabbit::Freeze(void)
{
    static int skin_id;

    if( direction > 0 )
    {
        skin_id = 1;
    }
    else
    {
        skin_id = 0;
    }

    skin = battack_skin + skin_id;
}

void FlyingRabbit::BeenAttack(int been_attack_val)
{
    freeze_clock = clock();
    freezing = true;
    health_point -= been_attack_val;
}

void FlyingRabbit::Move(double x, double y)
{
    static unsigned skin_id=0;

    if( x>0 )
    {
        skin_id = 1;
    }
    else if( x<0 )
    {
        skin_id = 0;
    }

    skin = normal_skin + skin_id;

    character_block.Move(x,y);
}

void FlyingRabbit::Attack(void)
{
    Block player_block;

    player_block = player->Getcharacter_block();

    if( player_block.IsInside( this->Getposition() ) )
    {
        player->Setbeen_attack(true);
    }
}

void FlyingRabbit::AI(void)
{
    if( !freezing )
    {
        Point destination;
        Point posision;
        double theta;
        double delta_x, delta_y;

        destination = player->Getposition();
        posision = character_block.Getcenter();
        theta = posision.ThetaTo( destination );

        delta_x = speed*cos(theta);
        delta_y = speed*sin(theta);

        if( delta_x > 0 )
        {
            direction = 1;
        }
        else
        {
            direction = -1;
        }

        Move(delta_x,delta_y);
        Attack();
    }
}

void FlyingRabbit::UpDateSatu(void)
{
    if( clock() - freeze_clock >= FREEZE_TIME )
    {
        freezing = false;
    }

    if( clock() - freeze_clock <= FREEZE_TIME && freezing )
    {
        Freeze();
    }

}






