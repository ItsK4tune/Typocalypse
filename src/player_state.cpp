#include "player_state.h"

PlayerIdleState::PlayerIdleState() {}
PlayerIdleState &PlayerIdleState::getInstance()
{
    static PlayerIdleState instance;
    return instance;
}

void PlayerIdleState::enter(Player *player)
{
    // player->changeState(&PlayerIdleState::getInstance());
}
void PlayerIdleState::update(Player *player, float deltaTime)
{
    player->update(deltaTime);
}
void PlayerIdleState::exit(Player *player)
{
}

