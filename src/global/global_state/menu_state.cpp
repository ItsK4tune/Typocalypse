#include "global/global_state.h"
#include <utilities/init.h>

GlobalMenuState::GlobalMenuState() {}
GlobalMenuState &GlobalMenuState::getInstance()
{
    static GlobalMenuState instance;
    return instance;
}
void GlobalMenuState::enter(Global *global)
{
}
void GlobalMenuState::update(Global *global, float deltaTime)
{
    global->display->update(deltaTime);
    // global->drawText();

    if (global->game.isMousePressed &&
        global->game.mouseX >= 0 &&
        global->game.mouseX <= global->screenWidth &&
        global->game.mouseY >= 0 &&
        global->game.mouseY <= global->screenHeight)
    {
        global->changeState(&GlobalPlayState::getInstance());
    }
}
void GlobalMenuState::exit(Global *global)
{
    global->game.isMousePressed = false;
}