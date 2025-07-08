#pragma once

#include "state.h"
#include "enemy/enemy.h"

class EnemyRespawnState : public State<EnemyAbstract>
{
public:
    static EnemyRespawnState &getInstance();

    void enter(EnemyAbstract *enemy) override;
    void update(EnemyAbstract *enemy, float deltaTime) override;
    void exit(EnemyAbstract *enemy) override;
private:
    EnemyRespawnState();
};