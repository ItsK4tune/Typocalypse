#pragma once

#include "global.h"
#include "enemy_state.h"
#include "spawn_enemy.h"

void checkWord() {
    for (auto &e : Global::enemies)
    {
        if (e->getWord() == Global::currentTypedWord)
        {
            e->getStateMachine().changeState(&EnemyDieState::getInstance());
            trySpawnOneEnemy(Global::playerPosition);
        }
    }
}