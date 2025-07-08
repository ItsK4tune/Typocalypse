#include "pool/creep_enemy_pool.h"

#include <iostream>
#include <algorithm>
#include <random>

#include "enemy/enemy_state.h"
#include "utilities/genMesh.h"

void CreepEnemyPool::init(size_t count, const Shader &shader, const std::vector<std::string> &wordList) {
    AABB localAABB = initTriangleMesh();
    enemies.clear();

    std::vector<std::string> fullWordList;

    if (wordList.empty()) {
        std::cerr << "[CreepEnemyPool::init] wordList is empty!\n";
        return;
    }

    while (fullWordList.size() < count) {
        fullWordList.insert(fullWordList.end(), wordList.begin(), wordList.end());
    }

    fullWordList.resize(count);

    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(fullWordList.begin(), fullWordList.end(), rng);

    for (size_t i = 0; i < count; ++i) {
        auto enemyModel = std::make_shared<Model>(enemyVertices, enemyIndices);
        enemyModel->setShader(std::make_shared<Shader>(shader));
        auto e = std::make_shared<CreepEnemy>(enemyModel);
        e->setLocalAABB(localAABB);
        e->setWord(fullWordList[i]);
        enemies.push_back(e);
    }
}

void CreepEnemyPool::clear()
{
    enemies.clear();
    enemyVertices.reset();
    enemyIndices.reset();
}

CreepEnemy* CreepEnemyPool::spawn()
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

void CreepEnemyPool::add(std::shared_ptr<CreepEnemy> e){
    enemies.push_back(e);
}

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

AABB CreepEnemyPool::initTriangleMesh()
{
    generatetriangleMesh(enemyVertices, enemyIndices, 0.07f, 0.07f, glm::vec3(1.0f, 1.0f, 0.0f));

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