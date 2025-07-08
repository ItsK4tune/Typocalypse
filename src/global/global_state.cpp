#include "global_state.h"
#include "utilities/spawn_enemy.h"

GlobalMenuState::GlobalMenuState() {}
GlobalMenuState &GlobalMenuState::getInstance()
{
    static GlobalMenuState instance;
    return instance;
}
void GlobalMenuState::enter(Global *global)
{
    printf("Entering GlobalMenuState\n");
}
void GlobalMenuState::update(Global *global, float deltaTime)
{
    global->drawText();

    if (global->game.isMousePressed &&
        global->game.mouseX >= 0 &&
        global->game.mouseX <= global->screenWidth &&
        global->game.mouseY >= 0 &&
        global->game.mouseY <= global->screenHeight)
    {
        printf("Mouse pressed, changing to play state\n");
        global->changeState(&GlobalPlayState::getInstance());
    }
}
void GlobalMenuState::exit(Global *global)
{
    global->game.isMousePressed = false;
}

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
        if (!respawnRandomEnemy())
            break;
        Global::getInstance().enemy.currentEnemyCount++;
    }
}
void GlobalPlayState::exit(Global *global)
{
}
