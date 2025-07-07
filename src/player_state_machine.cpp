#include "player_state_machine.h"
#include "player_state.h"

PlayerStateMachine::PlayerStateMachine(Player *e)
    : StateMachine<Player>(e)
{
    // changeState(&EnemyDieState::getInstance());
}