#pragma once

#include "state.h"
#include "bullet/bullet.h"

class BulletFlyingState : public State<Bullet>
{
public:
    static BulletFlyingState &getInstance();

    void enter(Bullet *enemy) override;
    void update(Bullet *enemy, float deltaTime) override;
    void exit(Bullet *enemy) override;

private:
    BulletFlyingState();
};