#include "global_state.h"

auto& global = Global::getInstance();

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
    // Simulate some menu logic, e.g., waiting for user input
    static float elapsedTime = 0.0f;
    elapsedTime += deltaTime;
    
    if (elapsedTime >= 5.0f) // After 5 seconds, switch to play state
    {
        elapsedTime = 0.0f;
        global->changeState(&GlobalPlayState::getInstance());
        printf("Switching to GlobalPlayState\n");
    }
}
void GlobalMenuState::exit(Global *global)
{
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


