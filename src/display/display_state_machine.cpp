#include "display/display_state_machine.h"
#include "display/display_state.h"

DisplayStateMachine::DisplayStateMachine(Display *e)
    : StateMachine<Display>(e)
{
    changeState(&DisplayMainState::getInstance());
}