#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <vector>
#include <FlyingRabbit.h>
#include <Camera.h>
#include <Player.h>

#define FLTING_RABBIT_TYPE 0

class Enemy
{
public:
    Enemy();
    ~Enemy();

    void Prepare(void);


    int GetNumerOf(int type);
    void New(Point posision,double speed,int type, Player& player);
    void DeleteAll(void);

    void BeenAttack(Block player_attack_block);
    void Show(Camera cam);
    void Action();
    void UpdateStatue();

private:

    std::vector<FlyingRabbit*> flying_rabbit;

};

#endif // ENEMY_H
