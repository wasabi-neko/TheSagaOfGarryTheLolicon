#include "Enemy.h"
#include <vector>

#include <stdio.h>
#include <Player.h>
#include <Point.h>
#include <Block.h>
#include <PlayerStatu.h>

extern unsigned FPS;


Enemy::Enemy()
{
    //ctor
}

Enemy::~Enemy()
{
    //dtor
}

int Enemy::GetNumerOf(int type)
{
    return flying_rabbit.size();
}

void Enemy::Prepare(void)
{
    for(int i=0; i<flying_rabbit.size(); i++)
    {
        flying_rabbit.at(i)->Prepare();
        flying_rabbit.at(i)->Activate();
    }
}

void Enemy::New(Point position,double speed, int type, Player& player)
{
    FlyingRabbit* new_rabbit;
    Block* temp;

    temp = new Block;

    temp->Setcenter( position );
    temp->Setheight( 20 );
    temp->Setwidth( 20 );


    new_rabbit = new FlyingRabbit;

    new_rabbit->Setspeed( speed/(double)FPS );
    new_rabbit->Setcharacter_block( *temp );
    new_rabbit->Setplayer( &player );
    new_rabbit->Prepare();

    flying_rabbit.push_back( new_rabbit );
}

void Enemy::DeleteAll(void)
{
    for(int i=0; i<flying_rabbit.size(); i++)
    {
        if( flying_rabbit.size() == 0 )
            break;

        flying_rabbit.erase( flying_rabbit.begin() );
    }
}

void Enemy::BeenAttack(Block player_attack_block)
{
    for(int i=0; i<flying_rabbit.size(); i++)
    {
        FlyingRabbit* temp;

        temp = flying_rabbit.at(i);
        if( player_attack_block.IsInside( temp->Getposition() ) )
        {
            temp->BeenAttack(1);
        }
    }
}

void Enemy::Show(Camera cam)
{
    if( flying_rabbit.size() != 0 )
    {
        for(int i=0; i<flying_rabbit.size(); i++)
        {
            flying_rabbit.at(i)->Show(cam);
        }
    }
}

void Enemy::Action(void)
{
    if( flying_rabbit.size() != 0)
    {
        for(int i=0; i<flying_rabbit.size(); i++)
        {
            flying_rabbit.at(i)->AI();
        }
    }
}

void Enemy::UpdateStatue(void)
{

    for(int i=0; i<flying_rabbit.size(); i++)
    {
        if( flying_rabbit.size() == 0)
            break;


        if( flying_rabbit.at(i)->IsDead() )
        {
            flying_rabbit.erase( flying_rabbit.begin() + i );
            PlayerStatu::score += 100;
            printf("score:%04d\n", PlayerStatu::score);
            i--;
        }
        else
        {
            flying_rabbit.at(i)->UpDateSatu();
        }
    }
}











