#pragma once

#include "state.h"
#include "bullet/bullet.h"

class BulletDieState : public State<Bullet>
{
public:
    static BulletDieState &getInstance();

    void enter(Bullet *enemy) override;
    void update(Bullet *enemy, float deltaTime) override;
    void exit(Bullet *enemy) override;

private:
    BulletDieState();
};