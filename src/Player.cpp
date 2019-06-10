#include "Player.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>

#include <Point.h>
#include <Block.h>
#include <Camera.h>
#include <Enemy.h>

/*
    SPEED: (pixel/sec)
*/

//basic Data
#define SPEED 400
#define GRAVITY 1000 //1000
#define MAX_HEALTH_POINT 5
#define MAX_JUMP_HEIGHT_HIGH 120    //120
#define MAX_JUMP_HEIGHT_LOW 80
#define ATTACK_VALUE 1

//player block
#define PLAYER_BLOCK_WIDTH 20
#define PLAYER_BLOCK_HEIGHT 46

#define SKIN_DIFFERECE_X 5
#define SKIN_DIFFERECE_Y 0

//clock
#define SKIN_FLUSH_TIME 50  // 0.001 sec
#define ATTACK_SKIN_FLUSH_TIME  70
#define NULL_SKIN_FLUSH_TIME 250
#define HEALTH_POINT_LOCK_TIME 1000
#define ATTACK_TIME_CLOCK 210
#define MAX_FLY_TIME 200

//attack_block
#define ATTACK_BLOCK_VECTORX 15
#define ATTACK_BLOCK_VECTORY 0
#define ATTACK_BLOCK_WIDTH 25
#define ATTACK_BLOCK_HEIGHT 20

bool Player::player_left_key   = false;
bool Player::player_right_key  = false;
bool Player::player_jump_key   = false;
bool Player::player_attack_key = false;

long Player::walkl_skin_clock = -SKIN_FLUSH_TIME;
long Player::walkr_skin_clock = -SKIN_FLUSH_TIME;
long Player::jump_skin_clock  = -SKIN_FLUSH_TIME;
long Player::fall_skin_clock  = -SKIN_FLUSH_TIME;
long Player::attack_skin_clock = -ATTACK_SKIN_FLUSH_TIME;
long Player::null_skin_clock = -NULL_SKIN_FLUSH_TIME;
long Player::health_lock_clock = 0;
long Player::attack_time_clock = -ATTACK_TIME_CLOCK;

extern unsigned FPS;

Player::Player()
{
    //ctor

    this->Setspeed( SPEED/(double)FPS );
    this->Setmax_jump_height( MAX_JUMP_HEIGHT_HIGH );
    this->Setattack_value( ATTACK_VALUE );
    this->Setgravity( GRAVITY/(double)FPS );

    this->max_health_point = MAX_HEALTH_POINT;
    this->health_point = MAX_HEALTH_POINT;

    this->attack_key_lock = false;

    Block* block_ptr;
    block_ptr = new Block;

    block_ptr->Setcenter( Point(200,200) );
    block_ptr->Setwidth( PLAYER_BLOCK_WIDTH );
    block_ptr->Setheight( PLAYER_BLOCK_HEIGHT );
    this->Setcharacter_block( *block_ptr );

    this->skin_difference = Point( SKIN_DIFFERECE_X, SKIN_DIFFERECE_Y);
}

Player::~Player()
{
    //dtor
    free(stand_skin);
    free(walk_skin);
    free(jump_skin);
    free(attack_skin);
}


//Getter Function
Image Player::Getstand_skin(unsigned short index)
{
    if( index>=0 && index<3)
        return stand_skin[index];
    else
    {
        printf("warning from player::Getstand_skin : out of range\n");
    }
}

Image Player::Getwalk_skin(unsigned short index)
{
    if( index>=0 && index<3)
        return walk_skin[index];
    else
    {
        printf("warning from player::Getwalk_skin : out of range\n");
    }
}

Image Player::Getjump_skin(unsigned short index)
{
    if( index>=0 && index<3)
        return jump_skin[index];
    else
    {
        printf("warning from player::Getjump_skin : out of range\n");
    }
}

Image Player::Getattack_skin(unsigned short index)
{
    if( index>=0 && index<3)
        return attack_skin[index];
    else
    {
        printf("warning from player::Getattack_skin: out of range\n");
    }
}


//Setter Function
void Player::Setstand_skin(Image &val, unsigned short index)
{
    if( index>=0 && index<3)
        stand_skin[index] = val;
    else
    {
        printf("warning from player::Setstand_skin : out of range\n");
    }
}

void Player::Setwalk_skin(Image &val, unsigned short index)
{
    if( index>=0 && index<3)
        walk_skin[index] = val;
    else
    {
        printf("warning from player::Setwalk_skin : out of range\n");
    }
}

void Player::Setjump_skin(Image &val, unsigned short index)
{
    if( index>=0 && index<3)
        jump_skin[index] = val;
    else
    {
        printf("warning from player::Setjump_skin : out of range\n");
    }
}

void Player::Setattack_skin(Image &val, unsigned short index)
{
    if( index>=0 && index<3)
        attack_skin[index] = val;
    else
    {
        printf("warning from player::Setattack_skin: out of range\n");
    }
}


//Player Action
void Player::Prepare(void)
{
    //read skin
    char* s;
    s = new char[50];

    for(int i=0; i<2; i++)
    {
        sprintf(s,"character_skin//stand%d.png",i);
        stand_skin[i].ReadImg(s);
        stand_skin[i].UploadTexture();
        stand_skin[i].ReleaseImg();
    }
    printf("stand_skin \n");

    for(int i=0; i<8; i++)
    {
        sprintf(s,"character_skin//walk%d.png",i);
        walk_skin[i].ReadImg(s);
        walk_skin[i].UploadTexture();
        walk_skin[i].ReleaseImg();
    }
    printf("walk_skin\n");

    for(int i=0; i<4; i++)
    {
        sprintf(s,"character_skin//jump%d.png",i);
        jump_skin[i].ReadImg(s);
        jump_skin[i].UploadTexture();
        jump_skin[i].ReleaseImg();
    }
    printf("jump_skin\n");

    for(int i=0; i<6; i++)
    {
        sprintf(s,"character_skin//attack%d.png",i);
        attack_skin[i].ReadImg(s);
        attack_skin[i].UploadTexture();
        attack_skin[i].ReleaseImg();
    }
    printf("attack_skin\n");

    delete s;

    null_skin.ReadImg("character_skin//null.png");
    null_skin.UploadTexture();

    //end read skin
}

void Player::Stand(void)
{
    if( direction < 0)  //skin[0] =>left
    {
        skin = stand_skin;
    }
    else if( direction >= 0)
    {
        skin = stand_skin+1;
    }
}

void Player::Walk(void)
{
    static unsigned skin_id = 0; //0,1,2,3,,,4,5,6,7
    long delta_time;

    if( direction < 0)//left
    {
        delta_time = clock() - walkl_skin_clock;

        if( delta_time >= SKIN_FLUSH_TIME && grounded)
        {
            skin_id = (skin_id>=3)? 0 : skin_id+1;
            skin = walk_skin + skin_id;

            walkl_skin_clock = clock();
        }

        MoveL(speed);
    }
    else if( direction >= 0 )//right
    {
        delta_time = clock() - walkr_skin_clock;

        if( delta_time >= SKIN_FLUSH_TIME && grounded)
        {
            skin_id = (skin_id>=7)? 4 : skin_id+1;
            skin = walk_skin + skin_id;

            walkr_skin_clock = clock();
        }

        MoveR(speed);
    }
}

void Player::Jump(void)
{
    static unsigned skin_id = 0; //0,1,2,3
    static long fly_time;               // make player fly and not to fall immediately, when it comes to max_jump_height
    const long max_fly_time = MAX_FLY_TIME;
    long delta_time;

    delta_time = clock() - jump_skin_clock;


    if( delta_time >= SKIN_FLUSH_TIME )// swap skin
    {
        if( direction < 0)
        {
            skin_id = (skin_id>=1)? 0 : skin_id+1;
            skin = jump_skin + skin_id;
        }
        else
        {
            skin_id = (skin_id>=3)? 2 : skin_id+1;
            skin = jump_skin + skin_id;
        }

        jump_skin_clock = clock();
    }

    if( jump_height <= max_jump_height)
    {
        MoveUp(gravity);
        jump_height += gravity;

        fly_time = clock();
    }
    else
    {
        if( (clock() - fly_time) >= max_fly_time )
        {
            jumping = false;
            jump_height = 0;
        }
    }
}

void Player::Fall(void)
{
    static unsigned skin_id = 0; //0,1,2,3
    long delta_time;


    delta_time = clock() - fall_skin_clock;

    if( delta_time >= SKIN_FLUSH_TIME )
    {
        if( direction < 0)
        {
            skin_id = (skin_id>=1)? 0 : skin_id+1;
            skin = jump_skin + skin_id;
        }
        else
        {
            skin_id = (skin_id>=3)? 2 : skin_id+1;
            skin = jump_skin + skin_id;
        }

        fall_skin_clock = clock();
    }

    MoveDown(gravity);
}

Block Player::GetAttackBlock(void)
{
    Block re;

    re.Setcenter( this->Getposition() );
    re.Move( direction*ATTACK_BLOCK_VECTORX, ATTACK_BLOCK_VECTORY );

    re.Setwidth( ATTACK_BLOCK_WIDTH );
    re.Setheight( ATTACK_BLOCK_HEIGHT );

    return re;
}

void Player::Attack()
{
    static unsigned skin_id = 0; //0,1,2,,3,4,5
    long delta_time;
    Block attack_area;
    extern Enemy enemy;


    delta_time = clock() - attack_skin_clock;

    if( delta_time >= ATTACK_SKIN_FLUSH_TIME )//skin
    {
        if( direction < 0)
        {
            skin_id = (skin_id>=2)? 0 : skin_id+1;
            skin = attack_skin + skin_id;
        }
        else
        {
            skin_id = (skin_id>=5)? 3 : skin_id+1;
            skin = attack_skin + skin_id;
        }

        attack_skin_clock = clock();
    }



    attack_area = GetAttackBlock();
    enemy.BeenAttack( attack_area );
}

void Player::BeenAttack(int attack_val,int push_val)
{
    health_point_lock = true;
    health_lock_clock = clock();

    health_point--;
    printf("HP:%d\n",health_point);
    Beep(700,30);
}


void Player::Control(void)
{
    if( player_left_key && player_right_key )
    {
        walking = false;
    }
    else
    {
        if( player_left_key )
        {
            direction = -1;
            walking = true;
        }

        if( player_right_key )
        {
            direction = 1;
            walking = true;
        }
    }

    if( (!player_left_key)&&(!player_right_key) )
    {
        walking = false;
    }

    if( player_jump_key )
    {
        if( grounded )
        {
            max_jump_height = MAX_JUMP_HEIGHT_HIGH;
            jump_height = 0;
            jumping = true;
        }
    }
    else
    {

        jumping = false;
//        if( jump_height > MAX_JUMP_HEIGHT_LOW+10 )
//        {
//            max_jump_height = MAX_JUMP_HEIGHT_HIGH;
//        }
//        else
//        {
//            max_jump_height = MAX_JUMP_HEIGHT_LOW;
//        }
    }


    if( player_attack_key )
    {
        if( !attack_key_lock )
        {
            attack_key_lock = true;
            attack_time_clock = clock();
        }
    }
    else
    {
        attack_key_lock = false;
    }


    if( !walking && !jumping && grounded )
    {
        standing = true;
    }
    else
    {
        standing = false;
    }

}

void Player::UpdateStatu(void)
{
    if( Getawake() )
    {
        if( standing )
        {
            Stand();
        }

        if( walking )
        {
            Walk();
        }

        if(jumping)
        {
            Jump();
        }

        if( !grounded && !jumping )
        {
            Fall();
        }

        if( clock() - attack_time_clock <= ATTACK_TIME_CLOCK )
        {
            Attack();
        }

        if( beening_attack && (!health_point_lock ) )
        {
            BeenAttack(1,10);
        }

        if( health_point_lock == true )
        {
            beening_attack = false;

            if( (clock()-null_skin_clock) >= NULL_SKIN_FLUSH_TIME )
            {
                skin = &null_skin;
                null_skin_clock = clock();
            }

            if( (clock()-health_lock_clock) >= HEALTH_POINT_LOCK_TIME )
            {
                health_point_lock = false;
            }
        }
    }
}




















