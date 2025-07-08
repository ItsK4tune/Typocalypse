#pragma once

#include "state.h"
#include "bullet/bullet.h"

class BulletOnHitState : public State<Bullet>
{
public:
    static BulletOnHitState &getInstance();

    void enter(Bullet *enemy) override;
    void update(Bullet *enemy, float deltaTime) override;
    void exit(Bullet *enemy) override;

private:
    BulletOnHitState();
};