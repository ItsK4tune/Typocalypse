#include "enemy/enemy_state.h"

EnemyMoveState::EnemyMoveState() {}
EnemyMoveState &EnemyMoveState::getInstance()
{
    static EnemyMoveState instance;
    return instance;
}
void EnemyMoveState::enter(EnemyAbstract *enemy)
{
}
void EnemyMoveState::update(EnemyAbstract *enemy, float deltaTime)
{
    enemy->updateModelRotation(deltaTime);
    enemy->move(deltaTime);
    enemy->draw();
    enemy->drawText();

    if (enemy->getStats()->numberOfUnique)
        enemy->uniqueTrigger(deltaTime);
}
void EnemyMoveState::exit(EnemyAbstract *enemy)
{
}
