#include "pool/charge_enemy_pool.h"

#include <iostream>
#include <algorithm>
#include <random>

#include "enemy/enemy_state.h"
#include "utilities/genMesh.h"
#include "resource_manager/resource_manager.h"

void ChargeEnemyPool::init(size_t count, const Shader &shader, const std::vector<std::string> &wordList)
{
    AABB localAABB = initTriangleMesh();
    enemies.clear();

    std::vector<std::string> fullWordList;

    if (wordList.empty())
    {
        std::cerr << "[ChargeEnemyPool::init] wordList is empty!\n";
        return;
    }

    while (fullWordList.size() < count)
    {
        fullWordList.insert(fullWordList.end(), wordList.begin(), wordList.end());
    }

    fullWordList.resize(count);

    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(fullWordList.begin(), fullWordList.end(), rng);

    for (size_t i = 0; i < count; ++i)
    {
        auto enemyModel = std::make_shared<Model>(*ResourceManager::getInstance().getModel("enemy"));
        enemyModel->setShader(ResourceManager::getInstance().getShader("default"));
        auto e = std::make_shared<ChargeEnemy>(enemyModel);
        e->setLocalAABB(enemyModel->getAABB());
        e->setWord(fullWordList[i]);
        enemies.push_back(e);
    }
}

void ChargeEnemyPool::clear()
{
    enemies.clear();
    enemyVertices.reset();
    enemyIndices.reset();
}

ChargeEnemy *ChargeEnemyPool::spawn()
{
    std::vector<int> deadIndices;

    for (int i = 0; i < enemies.size(); ++i)
    {
        if (enemies[i]->getStateMachine().getCurrentState() == &EnemyDieState::getInstance())
        {
            deadIndices.push_back(i);
        }
    }

    if (deadIndices.empty())
        return nullptr;

    int randomIndex = deadIndices[rand() % deadIndices.size()];
    auto &enemy = enemies[randomIndex];

    enemy->changeState(&EnemyRespawnState::getInstance());
    return enemy.get();
}

void ChargeEnemyPool::add(std::shared_ptr<ChargeEnemy> e)
{
    enemies.push_back(e);
}

void ChargeEnemyPool::updateCurrentEnemyCount()
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

AABB ChargeEnemyPool::initTriangleMesh()
{
    generatetriangleMesh(enemyVertices, enemyIndices, 0.07f, 0.07f, glm::vec3(0.0f, 0.0f, 1.0f));

    if (!enemyVertices || enemyVertices->empty())
    {
        std::cerr << "[BulletPool::initRectangleMesh] bulletVertices is empty!\n";
        return AABB();
    }

    glm::vec3 min = enemyVertices->at(0).position;
    glm::vec3 max = min;

    for (size_t i = 1; i < enemyVertices->size(); ++i)
    {
        const glm::vec3 &pos = enemyVertices->at(i).position;
        min = glm::min(min, pos);
        max = glm::max(max, pos);
    }

    return AABB(min, max);
}