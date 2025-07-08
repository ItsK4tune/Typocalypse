#pragma once

#include <memory>
#include <vector>

#include "enemy/enemy.h"

class CreepEnemyPool
{
public:
    std::vector<std::shared_ptr<CreepEnemy>> enemies;
    int maxEnemyCount = 1;
    int currentEnemyCount = 0;

    void clear();
    void add(std::shared_ptr<CreepEnemy> e);
    void updateCurrentEnemyCount();
};