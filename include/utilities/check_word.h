#pragma once

#include "global.h"
#include "enemy_state.h"
#include "spawn_enemy.h"

void checkWord() {
    for (auto &e : Global::getInstance().enemy.enemies)
    {
        if (e->getWord() == Global::getInstance().player.currentTypedWord)
        {
            e->getStateMachine().changeState(&EnemyDieState::getInstance());
            Global::getInstance().enemy.numberOfEnemies++;
        }
    }
}