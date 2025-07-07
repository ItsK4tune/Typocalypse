#pragma once

#include "state_machine.h"
class Player;

class PlayerStateMachine : public StateMachine<Player>
{
public:
    PlayerStateMachine(Player *e);
};
