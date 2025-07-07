#include "bullet_state_machine.h"
#include "bullet_state.h"

BulletStateMachine::BulletStateMachine(Bullet *e)
    : StateMachine<Bullet>(e)
{
    changeState(&BulletDieState::getInstance());
}