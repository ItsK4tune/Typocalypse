#pragma once

#include "global/global.h"
#include "enemy/enemy_state.h"
#include "utilities/text_match.h"

void checkWord()
{
    const std::string &typed = Global::getInstance().playerData.currentTypedWord;

    for (auto &e : Global::getInstance().enemies)
    {
        if (e->getStateMachine().getCurrentState() == &EnemyDieState::getInstance())
            continue;

        const std::string &targetWord = e->getWord();
        std::vector<bool> mask = getPrefixMatchMaskFromTypedEnd(targetWord, typed);

        bool matched = true;
        for (bool b : mask)
        {
            if (!b)
            {
                matched = false;
                break;
            }
        }

        if (matched)
        {
            std::shared_ptr<EnemyAbstract> target = e;
            Bullet *bullet = Global::getInstance().bulletPool.spawn(Global::getInstance().playerData.player->getModel()->getPosition(), target);
            e->changeState(&EnemyFreezeState::getInstance());
            break;
        }
    }

    Global::getInstance().playerData.currentTypedWord.clear();
}