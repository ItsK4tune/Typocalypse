#pragma once

#include "state_machine.h"
class EnemyAbstract;

class EnemyStateMachine : public StateMachine<EnemyAbstract>
{
public:
    EnemyStateMachine(EnemyAbstract *e);
};
