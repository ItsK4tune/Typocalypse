#pragma once

#include "state.h"
#include "enemy.h"
#include <iostream>

class EnemyIdleState : public State<EnemyAbstract>
{
public:
    static EnemyIdleState &getInstance();

    void enter(EnemyAbstract *enemy) override;
    void update(EnemyAbstract *enemy, float deltaTime) override;
    void exit(EnemyAbstract *enemy) override;

private:
    EnemyIdleState();
};

class EnemyMoveState : public State<EnemyAbstract>
{
public:
    static EnemyMoveState &getInstance();

    void enter(EnemyAbstract *enemy) override;
    void update(EnemyAbstract *enemy, float deltaTime) override;
    void exit(EnemyAbstract *enemy) override;

private:
    EnemyMoveState();
};
