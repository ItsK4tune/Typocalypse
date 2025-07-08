#include "pool/creep_enemy_pool.h"

#include "enemy/enemy_state.h"

void CreepEnemyPool::clear() { enemies.clear(); }
void CreepEnemyPool::add(std::shared_ptr<CreepEnemy> e) { enemies.push_back(e); }
void CreepEnemyPool::updateCurrentEnemyCount()
{
    currentEnemyCount = 0;
    for (auto &e : enemies)
    {
        if (e->getStateMachine().getCurrentState() != &EnemyDieState::getInstance())
        {
            currentEnemyCount++;
        }
    }
}