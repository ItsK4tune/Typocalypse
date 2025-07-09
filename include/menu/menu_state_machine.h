#pragma once

#include "state_machine.h"
class Menu;

class MenuStateMachine : public StateMachine<Menu>
{
public:
    MenuStateMachine(Menu *e);
};
