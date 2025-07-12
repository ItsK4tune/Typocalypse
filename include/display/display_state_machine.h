#pragma once

#include "state_machine.h"
class Display;

class DisplayStateMachine : public StateMachine<Display>
{
public:
    DisplayStateMachine(Display *e);
};
