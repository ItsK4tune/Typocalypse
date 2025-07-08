#include "enemy_state_machine.h"
#include "enemy_state.h"

EnemyStateMachine::EnemyStateMachine(EnemyAbstract *e)
    : StateMachine<EnemyAbstract>(e)
{
    changeState(&EnemyDieState::getInstance());
}