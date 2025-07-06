#include "global_state_machine.h"
#include "global_state.h"

GlobalStateMachine::GlobalStateMachine(Global *e)
    : StateMachine<Global>(e)
{
    changeState(&GlobalMenuState::getInstance());
}