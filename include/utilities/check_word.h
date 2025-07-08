#pragma once

#include "global.h"
#include "enemy_state.h"
#include "spawn_enemy.h"

void checkWord()
{
    auto &global = Global::getInstance();

    for (auto &e : global.enemy.enemies)
    {
        if (e->getStateMachine().getCurrentState() == &EnemyDieState::getInstance())
            continue;

        if (e->getWord() == global.player.currentTypedWord)
        {
            std::shared_ptr<EnemyAbstract> target = e;

            Bullet *bullet = global.bulletPool.spawn(global.player.position, target);

            e->changeState(&EnemyFreezeState::getInstance());

            break;
        }
    }

    // Clear typed word sau khi bắn
    global.player.currentTypedWord.clear();
}