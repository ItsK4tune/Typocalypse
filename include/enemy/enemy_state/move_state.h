#pragma once

#include "state.h"
#include "enemy/enemy.h"

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