#pragma once

#include "state.h"
#include "bullet.h"

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