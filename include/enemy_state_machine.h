#pragma once

class Enemy;
#include "state_machine.h"
#include "enemy.h"


class EnemyStateMachine : public StateMachine<Enemy> {
public:
    EnemyStateMachine(Enemy* e) : StateMachine<Enemy>(e) {}
};
