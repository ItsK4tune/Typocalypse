#include "global_state.h"

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
    if (elapsedTime >= 30.0f)
    {
        elapsedTime = 0.0f;
        global->enemy.numberOfEnemies += 3;
        printf("Number of enemies increased to: %d\n", global->enemy.numberOfEnemies);
    }
}
void GlobalPlayState::exit(Global *global)
{
}
