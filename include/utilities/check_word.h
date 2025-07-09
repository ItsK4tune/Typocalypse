#pragma once

#include "global/global.h"
#include "enemy/enemy_state.h"
#include "utilities/text_match.h"
#include <algorithm>

void checkWord()
{
    const std::string &typed = Global::getInstance().playerData.currentTypedWord;
    auto &player = Global::getInstance().playerData.player;

    float minDistance = std::numeric_limits<float>::max();
    std::shared_ptr<EnemyAbstract> target = nullptr;

    for (auto &e : Global::getInstance().enemies)
    {
        if (e->getStateMachine().getCurrentState() == &EnemyDieState::getInstance())
            continue;

        const std::string &targetWord = e->getWord();
        std::vector<bool> mask = getPrefixMatchMaskFromTypedEnd(targetWord, typed);

        bool matched = std::all_of(mask.begin(), mask.end(), [](bool b) { return b; });
        if (!matched)
            continue;

        float distance = glm::length(e->getModel()->getPosition() - player->getModel()->getPosition());

        if (distance < minDistance)
        {
            minDistance = distance;
            target = e;
        }
    }

    if (target)
    {
        Bullet *bullet = Global::getInstance().bulletPool.spawn(player->getModel()->getPosition(), target);
        target->changeState(&EnemyFreezeState::getInstance());
    }

    Global::getInstance().playerData.currentTypedWord.clear();
}