#include "bullet/bullet_state_machine.h"
#include "bullet/bullet_state.h"

BulletStateMachine::BulletStateMachine(Bullet *e)
    : StateMachine<Bullet>(e)
{
    changeState(&BulletDieState::getInstance());
}