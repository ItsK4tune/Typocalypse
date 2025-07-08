#pragma once

#include "state_machine.h"
class Global;

class GlobalStateMachine : public StateMachine<Global>
{
public:
    GlobalStateMachine(Global *e);
};