#include "player/player_state.h"

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