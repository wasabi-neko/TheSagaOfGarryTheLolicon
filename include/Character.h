#ifndef CHARACTER_H
#define CHARACTER_H

#include <Point.h>
#include <Block.h>
#include <Image.h>
#include <Camera.h>

class Character
{
public:
    Character();
    Character(Point location,int  width, int height, Image* skin, double speed, double gravity, int max_health_point, int attack_value);
    ~Character();

    bool Getawake(void) { return awake; }
    Block Getcharacter_block() { return character_block; }
    Point GetSkinPoint(void) { return character_block.Getcenter()+skin_difference; }
    Point Getposition() { return character_block.Getcenter(); }
    Image Getskin() { return *skin; }

    int Getmax_health_point() { return max_health_point; }
    int Gethealth_point() { return health_point; }
    bool Getheath_point_lock() { return health_point_lock; }

    double Getspeed() { return speed; }
    double Getgravity() { return gravity; }
    double Getjump_height() { return jump_height; }
    double Getmax_jump_height() { return max_jump_height; }
    int Getattack_value() { return attack_value; }

    bool Getwalking() { return walking; }
    bool Getattacking() { return attacking; }
    bool Getjumping() { return jumping; }
    bool Getgrounded() { return grounded; }

    bool IsDead(void);


    void Setawake(bool val) { awake = val; }
    void SetSkinDifference(Point val) { skin_difference = val; }
    void Setposision(Point val) { character_block.Setcenter( val ); }
    void Setcharacter_block(Block val) { character_block = val; }
    void Setskin(Image val) { skin = &val; }

    void Setattack_value(int val) { attack_value = val; }
    void Setspeed(double val) { speed = val; }
    void Setgravity(double val) { gravity = val; }
    void Setmax_jump_height(double val) { max_jump_height = val; }

    void Setwalking(bool val) { walking = val; }
    void Setattacking(bool val) { attacking = val; }
    void Setjumping(bool val) { jumping = val; }
    void Setgrounded(bool val) { grounded = val; }

    void Sethealth_point_lock(bool val) { health_point_lock = val; }


    void Activate(void) { awake = true; }
    void MoveL(double val);
    void MoveR(double val);
    void MoveUp(double val);
    void MoveDown(double val);
    void AddHealthPoint(int value);
    void Show(Camera cam);

protected:
    Block character_block;
    Point skin_difference;// vector// from character to skin_point
    bool awake;             //is active;
    int max_health_point;
    int health_point;
    int attack_value;
    double speed;
    double gravity;
    double jump_height;
    double max_jump_height;

    bool standing;
    bool walking;
    bool jumping;
    bool attacking;
    bool grounded;
    bool health_point_lock;
    Image *skin;
};

#endif // CHARACTER_H
