#pragma once

#include "state.h"
#include "enemy.h"

class EnemyFreezeState : public State<EnemyAbstract>
{
public: 
    static EnemyFreezeState &getInstance();

    void enter(EnemyAbstract *enemy) override;
    void update(EnemyAbstract *enemy, float deltaTime) override;
    void exit(EnemyAbstract *enemy) override;

private:
    EnemyFreezeState();
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


class EnemyDieState : public State<EnemyAbstract>
{
public:
    static EnemyDieState &getInstance();

    void enter(EnemyAbstract *enemy) override;
    void update(EnemyAbstract *enemy, float deltaTime) override;
    void exit(EnemyAbstract *enemy) override;
private:
    EnemyDieState();
};