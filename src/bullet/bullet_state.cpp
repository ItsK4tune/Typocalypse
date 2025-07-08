#include "bullet_state.h"

BulletFlyingState::BulletFlyingState() {}
BulletFlyingState &BulletFlyingState::getInstance()
{
    static BulletFlyingState instance;
    return instance;
}
void BulletFlyingState::enter(Bullet *bullet)
{
    bullet->setVelocity(glm::vec3(0.0f));
    bullet->setAcceleration(glm::vec3(0.0f));
}
void BulletFlyingState::update(Bullet *bullet, float deltaTime)
{
    bullet->move(deltaTime);
    bullet->draw();
}
void BulletFlyingState::exit(Bullet *bullet)
{
}

BulletDieState::BulletDieState() {}
BulletDieState &BulletDieState::getInstance()
{
    static BulletDieState instance;
    return instance;
}
void BulletDieState::enter(Bullet *bullet)
{
    bullet->setVelocity(glm::vec3(0.0f));
    bullet->setAcceleration(glm::vec3(0.0f));
}
void BulletDieState::update(Bullet *bullet, float deltaTime)
{
    // bullet->draw();
}
void BulletDieState::exit(Bullet *bullet)
{
}

BulletOnHitState::BulletOnHitState() {}
BulletOnHitState &BulletOnHitState::getInstance()
{
    static BulletOnHitState instance;
    return instance;
}
void BulletOnHitState::enter(Bullet *bullet)
{
    // bullet->setVelocity(glm::vec3(0.0f));
    // bullet->setAcceleration(glm::vec3(0.0f));
}
void BulletOnHitState::update(Bullet *bullet, float deltaTime)
{
    // bullet->draw();
}
void BulletOnHitState::exit(Bullet *bullet)
{
}