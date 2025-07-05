#include "enemy_state.h"

EnemyIdleState::EnemyIdleState() {}

EnemyIdleState &EnemyIdleState::getInstance()
{
    static EnemyIdleState instance;
    return instance;
}

void EnemyIdleState::enter(EnemyAbstract *enemy)
{
    std::cout << "[EnemyIdleState] Enter: enemy idling\n";
}

void EnemyIdleState::update(EnemyAbstract *enemy, float deltaTime)
{
    enemy->setVelocity(glm::vec3(0.0f));
    enemy->setAcceleration(glm::vec3(0.0f));
}

void EnemyIdleState::exit(EnemyAbstract *enemy)
{
    std::cout << "[EnemyIdleState] Exit: enemy stop idling\n";
}

EnemyMoveState::EnemyMoveState() {}

EnemyMoveState &EnemyMoveState::getInstance()
{
    static EnemyMoveState instance;
    return instance;
}

void EnemyMoveState::enter(EnemyAbstract *enemy)
{
    std::cout << "[EnemyMoveState] Enter: enemy starts moving\n";
}

void EnemyMoveState::update(EnemyAbstract *enemy, float deltaTime)
{
    enemy->updateModelRotation(deltaTime);
    enemy->move(deltaTime);
}

void EnemyMoveState::exit(EnemyAbstract *enemy)
{
    std::cout << "[EnemyMoveState] Exit: enemy stops moving\n";
}