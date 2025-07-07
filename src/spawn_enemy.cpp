#include "utilities/spawn_enemy.h"

#include "utilities/genMesh.h"
#include "vertex.h"
#include "shader.h"
#include "model.h"
#include "enemy.h"
#include "global.h"
#include "enemy_state.h"

#include <random>
#include <algorithm>
#include <cstdlib>
#include <cmath>

Vertex *enemyVertices = nullptr;
GLuint *enemyIndices = nullptr;
unsigned int enemyVertexCount = 0;
unsigned int enemyIndexCount = 0;

void initTriangleMesh()
{
    generatetriangleMesh(enemyVertices, enemyIndices, enemyVertexCount, enemyIndexCount, 0.12f, 0.1f, glm::vec3(1.0f, 1.0f, 0.0f));
}

std::shared_ptr<CreepEnemy> initCreep(const std::string &word, const Shader &shader)
{
    auto enemyModel = std::make_shared<Model>(enemyVertices, enemyVertexCount, enemyIndices, enemyIndexCount);
    enemyModel->setShader(std::make_shared<Shader>(shader));

    auto creep = std::make_shared<CreepEnemy>(enemyModel);
    creep->setWord(word);

    glm::vec3 min = enemyVertices[0].position;
    glm::vec3 max = enemyVertices[0].position;
    for (unsigned int i = 1; i < enemyVertexCount; ++i)
    {
        min = glm::min(min, enemyVertices[i].position);
        max = glm::max(max, enemyVertices[i].position);
    }
    creep->setLocalAABB(AABB(min, max));

    return creep;
}

void initEnemyPool(const std::vector<std::string> &wordList, const Shader &shader)
{
    Global::getInstance().enemy.enemies.clear();
    for (const auto &word : wordList)
    {
        auto creep = initCreep(word, shader);
        Global::getInstance().enemy.enemies.push_back(creep);
    }
}

bool respawnRandomEnemy()
{
    auto &enemies = Global::getInstance().enemy.enemies;
    std::vector<std::shared_ptr<CreepEnemy>> deadEnemies;

    for (auto &e : enemies)
    {
        if (e->getStateMachine().getCurrentState() == &EnemyDieState::getInstance())
        {
            deadEnemies.push_back(e);
        }
    }

    if (!deadEnemies.empty())
    {
        std::shuffle(deadEnemies.begin(), deadEnemies.end(), std::default_random_engine(static_cast<unsigned int>(time(nullptr))));
        auto &chosen = deadEnemies.front();
        chosen->changeState(&EnemyRespawnState::getInstance());
        return true;
    }

    return false;
}

void deleteTriangleMesh()
{
    delete[] enemyVertices;
    delete[] enemyIndices;
    enemyVertices = nullptr;
    enemyIndices = nullptr;
    enemyVertexCount = 0;
    enemyIndexCount = 0;
}
