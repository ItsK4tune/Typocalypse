#include "global/global_state.h"

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