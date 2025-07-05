#include "enemy_state.h"

EnemyFreezeState::EnemyFreezeState() {}
EnemyFreezeState &EnemyFreezeState::getInstance()
{
    static EnemyFreezeState instance;
    return instance;
}
void EnemyFreezeState::enter(EnemyAbstract *enemy)
{
    enemy->setVelocity(glm::vec3(0.0f));
    enemy->setAcceleration(glm::vec3(0.0f));
}
void EnemyFreezeState::update(EnemyAbstract *enemy, float deltaTime)
{
    enemy->draw();
}
void EnemyFreezeState::exit(EnemyAbstract *enemy)
{
}

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
}
void EnemyMoveState::exit(EnemyAbstract *enemy)
{
}

EnemyDieState::EnemyDieState() {}
EnemyDieState &EnemyDieState::getInstance()
{
    static EnemyDieState instance;
    return instance;
}
void EnemyDieState::enter(EnemyAbstract *enemy)
{
    enemy->setVelocity(glm::vec3(0.0f));
    enemy->setAcceleration(glm::vec3(0.0f));
}
void EnemyDieState::update(EnemyAbstract *enemy, float deltaTime)
{
}
void EnemyDieState::exit(EnemyAbstract *enemy)
{
}