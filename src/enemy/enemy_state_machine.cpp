#include "enemy/enemy_state_machine.h"
#include "enemy/enemy_state.h"

EnemyStateMachine::EnemyStateMachine(EnemyAbstract *e)
    : StateMachine<EnemyAbstract>(e)
{
    changeState(&EnemyDieState::getInstance());
}