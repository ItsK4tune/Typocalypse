#include "player_state.h"

PlayerIdleState::PlayerIdleState() {}
PlayerIdleState &PlayerIdleState::getInstance()
{
    static PlayerIdleState instance;
    return instance;
}
void PlayerIdleState::enter(Player *player)
{
}
void PlayerIdleState::update(Player *player, float deltaTime)
{
    player->draw();
}
void PlayerIdleState::exit(Player *player)
{
}

PlayerDieState::PlayerDieState() {}
PlayerDieState &PlayerDieState::getInstance()
{
    static PlayerDieState instance;
    return instance;
}
void PlayerDieState::enter(Player *player)
{
}
void PlayerDieState::update(Player *player, float deltaTime)
{
    player->update(deltaTime);
}
void PlayerDieState::exit(Player *player)
{
}
