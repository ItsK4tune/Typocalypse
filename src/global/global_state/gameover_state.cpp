#include "global/global_state.h"

GlobalGameOverState::GlobalGameOverState() {}
GlobalGameOverState &GlobalGameOverState::getInstance()
{
    static GlobalGameOverState instance;
    return instance;
}
void GlobalGameOverState::enter(Global *global)
{
    printf("Entering GlobalGameOverState\n");
}
void GlobalGameOverState::update(Global *global, float deltaTime)
{
}
void GlobalGameOverState::exit(Global *global)
{
}