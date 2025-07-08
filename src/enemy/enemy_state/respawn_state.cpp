#include "enemy/enemy_state.h"
#include "global/global.h"

EnemyRespawnState::EnemyRespawnState() {}
EnemyRespawnState &EnemyRespawnState::getInstance()
{
    static EnemyRespawnState instance;
    return instance;
}
void EnemyRespawnState::enter(EnemyAbstract *enemy)
{
    enemy->setVelocity(glm::vec3(0.0f));
    enemy->setAcceleration(glm::vec3(0.0f));
    enemy->setMaxSpeed(0.5f);
    enemy->setAccelerationRate(3.0f);

    float x = -3.0f + static_cast<float>(rand()) / RAND_MAX * 6.0f;
    float y = sqrt(9.0f - x * x) * (rand() % 2 == 0 ? 1.0f : -1.0f);
    glm::vec3 spawnPos(x, y, 0.0f);
    enemy->getModel()->setPosition(spawnPos);
    enemy->setDirection(glm::normalize(Global::getInstance().player.position - spawnPos));
}
void EnemyRespawnState::update(EnemyAbstract *enemy, float deltaTime)
{
    enemy->changeState(&EnemyMoveState::getInstance());
}
void EnemyRespawnState::exit(EnemyAbstract *enemy)
{
}