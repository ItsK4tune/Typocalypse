#include "menu/menu_state_machine.h"
#include "menu/menu_state.h"

MenuStateMachine::MenuStateMachine(Menu *e)
    : StateMachine<Menu>(e)
{
    changeState(&MenuMainState::getInstance());
}