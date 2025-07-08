#pragma once

#include "global/global.h"
#include "enemy/enemy_state.h"

void checkWord()
{
    for (auto &e : Global::getInstance().enemy.enemies)
    {
        if (e->getStateMachine().getCurrentState() == &EnemyDieState::getInstance())
            continue;

        if (e->getWord() == Global::getInstance().playerData.currentTypedWord)
        {
            std::shared_ptr<EnemyAbstract> target = e;
            Bullet *bullet = Global::getInstance().bulletPool.spawn(Global::getInstance().playerData.player->getModel()->getPosition(), target);
            e->changeState(&EnemyFreezeState::getInstance());
            break;
        }
    }

    Global::getInstance().playerData.currentTypedWord.clear();
}