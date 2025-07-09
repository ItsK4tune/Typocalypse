#pragma once

#include <memory>
#include <vector>

#include "enemy/enemy.h"
#include "shader.h"

class ChargeEnemyPool
{
public:
    std::vector<std::shared_ptr<ChargeEnemy>> enemies;
    int maxEnemyCount = 1;
    int currentEnemyCount = 0;

    void init(size_t count, const Shader &shader, const std::vector<std::string> &wordList);
    ChargeEnemy* spawn();
    void add(std::shared_ptr<ChargeEnemy> e);
    void clear();
    void updateCurrentEnemyCount();
private:
    std::shared_ptr<std::vector<Vertex>> enemyVertices;
    std::shared_ptr<std::vector<GLuint>> enemyIndices;

    AABB initTriangleMesh();
};