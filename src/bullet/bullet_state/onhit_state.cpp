#include "bullet/bullet_state.h"

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