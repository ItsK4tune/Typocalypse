#include "enemy_state.h"

#include "global.h"

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

    float x = -2.0f + static_cast<float>(rand()) / RAND_MAX * 4.0f;
    float y = sqrt(4.0f - x * x) * (rand() % 2 == 0 ? 1.0f : -1.0f);
    glm::vec3 spawnPos(x, y, 0.0f);
    enemy->getModel()->setPosition(spawnPos);
    enemy->setDirection(glm::normalize(Global::getInstance().player.position - spawnPos));
}
void EnemyRespawnState::update(EnemyAbstract *enemy, float deltaTime)
{
    enemy->draw();
    enemy->changeState(&EnemyMoveState::getInstance());
}
void EnemyRespawnState::exit(EnemyAbstract *enemy)
{
}