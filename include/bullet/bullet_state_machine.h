#pragma once

#include "state_machine.h"
class Bullet;

class BulletStateMachine : public StateMachine<Bullet>
{
public:
    BulletStateMachine(Bullet *e);
};
