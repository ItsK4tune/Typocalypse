#include "enemy/enemy_state.h"

EnemyFreezeState::EnemyFreezeState() {}
EnemyFreezeState &EnemyFreezeState::getInstance()
{
    static EnemyFreezeState instance;
    return instance;
}
void EnemyFreezeState::enter(EnemyAbstract *enemy)
{
    enemy->getStats()->velocity = glm::vec3(0.0f);
    enemy->getStats()->acceleration = glm::vec3(0.0f);
}
void EnemyFreezeState::update(EnemyAbstract *enemy, float deltaTime)
{
    enemy->draw();
}
void EnemyFreezeState::exit(EnemyAbstract *enemy)
{
}