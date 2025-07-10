#include "pool/creep_enemy_pool.h"

#include <iostream>
#include <algorithm>
#include <random>

#include "enemy/enemy_state.h"
#include "utilities/genMesh.h"
#include "utilities/shader_type.h"
#include "resource_manager/resource_manager.h"

void CreepEnemyPool::init(size_t count, const std::vector<std::string> &wordList)
{
    enemies.clear();

    std::vector<std::string> fullWordList;

    if (wordList.empty())
    {
        std::cerr << "[CreepEnemyPool::init] wordList is empty!\n";
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
        auto enemyModel = std::make_shared<Model>(*ResourceManager::getInstance().getModel(std::to_string(static_cast<int>(EnemyType::CreepEnemy))));
        enemyModel->setShader(ResourceManager::getInstance().getShader(std::to_string(static_cast<int>(ShaderType::Default))));
        auto e = std::make_shared<CreepEnemy>(enemyModel);
        e->setLocalAABB(enemyModel->getAABB());
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

CreepEnemy *CreepEnemyPool::spawn()
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

void CreepEnemyPool::add(std::shared_ptr<CreepEnemy> e)
{
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