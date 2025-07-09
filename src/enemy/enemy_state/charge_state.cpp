#include "enemy/enemy_state.h"

EnemyChargeState::EnemyChargeState() {}
EnemyChargeState &EnemyChargeState::getInstance()
{
    static EnemyChargeState instance;
    return instance;
}
void EnemyChargeState::enter(EnemyAbstract *enemy)
{
}
void EnemyChargeState::update(EnemyAbstract *enemy, float deltaTime)
{
    enemy->draw();
    enemy->drawText();
    if (enemy->uniqueMove(deltaTime))
        enemy->changeState(&EnemyMoveState::getInstance());
}
void EnemyChargeState::exit(EnemyAbstract *enemy)
{
}
