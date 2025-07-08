#include "player/player_state_machine.h"
#include "player/player_state.h"

PlayerStateMachine::PlayerStateMachine(Player *e)
    : StateMachine<Player>(e)
{
    changeState(&PlayerIdleState::getInstance());
}