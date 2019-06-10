#ifndef FLYINGRABBIT_H
#define FLYINGRABBIT_H

#include <Character.h>
#include <Player.h>


class FlyingRabbit : public Character
{
public:
    FlyingRabbit();
    ~FlyingRabbit();

    static long freeze_clock;

    void Setplayer(Player* ptr) { player = ptr; }

    void Prepare(void);

    void Freeze(void);
    void BeenAttack(int been_attack_val);
    void Attack(void);
    void Move(double x,double y);
    void AI(void);

    void UpDateSatu(void);

private:

    int direction;  // d>=0 -> right, d<0 ->left
    bool freezing;  //

    Player* player;
    Image normal_skin[2];
    Image battack_skin[2];
};

#endif // FLYINGRABBIT_H
