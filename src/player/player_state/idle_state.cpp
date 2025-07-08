#include "player/player_state.h"

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