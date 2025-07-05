#include "utilities/spawn_enemy.h"

#include "utilities/genMesh.h"
#include "vertex.h"
#include "shader.h"
#include "model.h"
#include "enemy.h"
#include "global.h"
#include "enemy_state.h"

#include <cstdlib>
#include <cmath>

std::shared_ptr<CreepEnemy> initCreep(const std::string &word, const Shader &shader)
{
    Vertex *enemyVertices = nullptr;
    GLuint *enemyIndices = nullptr;
    unsigned int enemyVertexCount = 0;
    unsigned int enemyIndexCount = 0;

    generatetriangleMesh(enemyVertices, enemyIndices, enemyVertexCount, enemyIndexCount, 0.12f, 0.1f, glm::vec3(1.0f, 1.0f, 0.0f));

    auto enemyModel = std::make_shared<Model>(enemyVertices, enemyVertexCount, enemyIndices, enemyIndexCount);
    enemyModel->setShader(std::make_shared<Shader>(shader));

    auto creep = std::make_shared<CreepEnemy>(enemyModel);
    creep->setWord(word);

    delete[] enemyVertices;
    delete[] enemyIndices;

    return creep;
}

void initEnemyPool(const std::vector<std::string>& wordList, const Shader& shader)
{
    Global::enemies.clear();
    for (const auto& word : wordList)
    {
        auto creep = initCreep(word, shader);
        creep->changeState(&EnemyDieState::getInstance());
        Global::enemies.push_back(creep);
    }
}

void trySpawnOneEnemy(const glm::vec3& playerPos)
{
    std::vector<std::shared_ptr<CreepEnemy>> dieEnemies;

    for (auto& e : Global::enemies)
    {
        if (e->getStateMachine().getCurrentState() == &EnemyDieState::getInstance())
        {
            dieEnemies.push_back(e);
        }
    }

    if (!dieEnemies.empty())
    {
        int randIndex = rand() % dieEnemies.size();
        auto creep = dieEnemies[randIndex];

        float x = -2.0f + static_cast<float>(rand()) / RAND_MAX * 4.0f;
        float y = sqrt(4.0f - x * x) * (rand() % 2 == 0 ? 1.0f : -1.0f);
        glm::vec3 spawnPos(x, y, 0.0f);

        creep->getModel()->setPosition(spawnPos);
        creep->setDirection(glm::normalize(playerPos - spawnPos));
        creep->changeState(&EnemyMoveState::getInstance());
    }
}

void spawnInitialEnemies(int n, const glm::vec3& playerPos)
{
    for (int i = 0; i < n; ++i)
    {
        trySpawnOneEnemy(playerPos);
    }
}
