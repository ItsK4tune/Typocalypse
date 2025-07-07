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
            // Spawn a bullet towards enemy
            std::shared_ptr<EnemyAbstract> target = e;

            Bullet *bullet = global.bulletPool.spawn(global.player.position, target);
            if (bullet)
            {
                bullet->setMaxSpeed(0.5f); // hoặc tốc độ bạn muốn
                // Optionally: bạn có thể set accelerationRate tại đây nếu cần
            }

            // Chỉ spawn 1 viên đạn cho enemy đúng chữ đầu tiên
            break;
        }
    }

    // Clear typed word sau khi bắn
    global.player.currentTypedWord.clear();
}