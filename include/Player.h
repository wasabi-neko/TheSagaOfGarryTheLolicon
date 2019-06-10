#ifndef PLAYER_H
#define PLAYER_H

#include <Image.h>
#include <Character.h>


class Player : public Character
{
public:
    Player();
    ~Player();

    static bool player_left_key;
    static bool player_right_key;
    static bool player_jump_key;
    static bool player_attack_key;

    static long walkl_skin_clock;    //the clock_value when press walk_key
    static long walkr_skin_clock;
    static long jump_skin_clock;
    static long fall_skin_clock;
    static long attack_skin_clock;
    static long null_skin_clock;
    static long health_lock_clock;
    static long attack_time_clock;


    int Getdirection(void) { return direction; }
    Image Getstand_skin(unsigned short index);
    Image Getwalk_skin(unsigned short index);
    Image Getjump_skin(unsigned short index);
    Image Getattack_skin(unsigned short index);


    void Setdirection(int val) { direction = val; }
    void Setbeen_attack(bool val) { beening_attack = val; }
    void Setstand_skin(Image &val, unsigned short inex);
    void Setwalk_skin(Image &val, unsigned short index);
    void Setjump_skin(Image &val, unsigned short index);
    void Setattack_skin(Image &val, unsigned short index);


    void Prepare(void);

    Block GetAttackBlock(void);

    void Stand(void);
    void Walk(void);
    void Jump(void);
    void Fall(void);
    void Attack(void);
    void BeenAttack(int attack_val, int push_val);

    void Control(void);
    void UpdateStatu(void);

private:

    int direction;  // -1 for left, 1 for right
    bool beening_attack;
    bool attack_key_lock;
    Image null_skin;
    Image stand_skin[2];
    Image attack_skin[6];   // 0~3 for left, 4~6 for right
    Image jump_skin[4];
    Image walk_skin[8];
};

#endif // PLAYER_H
