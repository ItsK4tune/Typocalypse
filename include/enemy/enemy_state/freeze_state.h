#pragma once

#include "state.h"
#include "enemy/enemy.h"

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