#pragma once

#include "state.h"
#include "enemy/enemy.h"

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