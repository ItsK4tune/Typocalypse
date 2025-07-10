#include "global/global_state.h"
#include "enemy/enemy_state.h"
#include "bullet/bullet_state.h"

GlobalPlayState::GlobalPlayState() {}
GlobalPlayState &GlobalPlayState::getInstance()
{
    static GlobalPlayState instance;
    return instance;
}
void GlobalPlayState::enter(Global *global)
{
    std::vector<std::string> wordList = {"cat", "dog", "fish", "bird", "mouse", "elephant", "giraffe", "lion", "tiger", "bear",
                                         "zebra", "monkey", "kangaroo", "panda", "rabbit", "fox", "wolf", "deer", "cow", "sheep"};

    Global::getInstance().playerData.init();
    Global::getInstance().creepEnemyPool.init(100, wordList);
    Global::getInstance().chargeEnemyPool.init(100, wordList);
    Global::getInstance().createPool();
}
void GlobalPlayState::update(Global *global, float deltaTime)
{
    static float elapsedTime = 0.0f;
    elapsedTime += deltaTime;
    if (elapsedTime >= 10.0f)
    {
        elapsedTime = 0.0f;
        // global->creepEnemyPool.maxEnemyCount += 1;
        global->chargeEnemyPool.maxEnemyCount += 1;
    }

    glm::mat4 projection = global->camera->getPerspectiveProjection(45.0f, (float)global->screenWidth / global->screenHeight, 0.1f, 100.0f);
    glm::mat4 view = global->camera->getViewMatrix();
    glm::mat4 mvp = projection * view * global->playerData.player->getModel()->getModelMatrix();
    global->playerData.player->getModel()->getShader()->use();
    global->playerData.player->getModel()->getShader()->setMat4("mvp", glm::value_ptr(mvp));
    global->playerData.player->update(deltaTime);

    global->creepEnemyPool.updateCurrentEnemyCount();
    while (global->creepEnemyPool.currentEnemyCount < global->creepEnemyPool.maxEnemyCount)
    {
        if (global->creepEnemyPool.spawn() != nullptr)
            break;
        global->creepEnemyPool.currentEnemyCount++;
    }

    global->chargeEnemyPool.updateCurrentEnemyCount();
    while (global->chargeEnemyPool.currentEnemyCount < global->chargeEnemyPool.maxEnemyCount)
    {
        if (global->chargeEnemyPool.spawn() != nullptr)
            break;
        global->chargeEnemyPool.currentEnemyCount++;
    }

    for (auto &b : global->bulletPool.bullets)
    {
        if (b->getStateMachine().getCurrentState() == &BulletFlyingState::getInstance())
        {
            b->getModel()->getShader()->use();
            b->getModel()->getShader()->setMat4("mvp", glm::value_ptr(projection * view * b->getModel()->getModelMatrix()));

            if (b->getWorldAABB().intersects(b->getTarget()->getWorldAABB()))
            {
                b->getTarget()->getStateMachine().changeState(&EnemyDieState::getInstance());
                b->getStateMachine().changeState(&BulletDieState::getInstance());
            }
        }

        b->update(deltaTime);
    }

    for (auto &e : global->enemies)
    {
        if (e->getStateMachine().getCurrentState() == &EnemyDieState::getInstance())
        {
            continue;
        }

        if (e->getWorldAABB().intersects(global->playerData.player->getWorldAABB()))
        {
            global->changeState(&GlobalGameOverState::getInstance());
        }

        e->getModel()->getShader()->use();
        e->getModel()->getShader()->setMat4("mvp", glm::value_ptr(projection * view * e->getModel()->getModelMatrix()));
        e->update(deltaTime);
    }
}
void GlobalPlayState::exit(Global *global)
{
}
