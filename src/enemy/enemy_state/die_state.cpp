#include "enemy/enemy_state.h"

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
