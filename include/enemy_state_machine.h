#pragma once

class EnemyAbstract;
#include "state_machine.h"
#include "enemy.h"

class EnemyStateMachine : public StateMachine<EnemyAbstract>
{
public:
    EnemyStateMachine(EnemyAbstract *e) : StateMachine<EnemyAbstract>(e) {}
};
