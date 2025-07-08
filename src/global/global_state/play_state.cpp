#include "global/global_state.h"

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

    Global::getInstance().enemy.updateCurrentEnemyCount();
    while (Global::getInstance().enemy.currentEnemyCount < Global::getInstance().enemy.maxEnemyCount)
    {
        if (global->enemy.spawn() != nullptr)
            break;
        Global::getInstance().enemy.currentEnemyCount++;
    }
}
void GlobalPlayState::exit(Global *global)
{
}
