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
}
void GlobalPlayState::update(Global *global, float deltaTime)
{
    static float elapsedTime = 0.0f;
    elapsedTime += deltaTime;
    if (elapsedTime >= 10.0f)
    {
        elapsedTime = 0.0f;
        global->enemy.maxEnemyCount += 1;
    }

    glm::mat4 projection = global->camera->getPerspectiveProjection(45.0f, (float)global->screenWidth / global->screenHeight, 0.1f, 100.0f);
    glm::mat4 view = global->camera->getViewMatrix();
    glm::mat4 mvp = projection * view * global->playerData.player->getModel()->getModelMatrix();
    global->playerData.player->getModel()->getShader()->use();
    global->playerData.player->getModel()->getShader()->setMat4("mvp", glm::value_ptr(mvp));
    global->playerData.player->update(deltaTime);

    global->enemy.updateCurrentEnemyCount();
    while (global->enemy.currentEnemyCount < global->enemy.maxEnemyCount)
    {
        if (global->enemy.spawn() != nullptr)
            break;
        global->enemy.currentEnemyCount++;
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

    for (auto &e : global->enemy.enemies)
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

    std::string typed = global->playerData.currentTypedWord;
    float scale = 1.0f, width = 0.0f;
    const auto &chars = global->text->getCharacters();
    for (char c : typed)
    {
        if (chars.count(c))
            width += (chars.at(c).advance >> 6) * scale;
    }
    float x = (global->screenWidth - width) / 2.0f;
    float y = 50.0f;
    global->text->renderText(typed, x, y, scale, glm::vec3(0.2f, 0.2f, 0.2f));
}
void GlobalPlayState::exit(Global *global)
{
}
