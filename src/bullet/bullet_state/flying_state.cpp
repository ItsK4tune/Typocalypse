#include "bullet/bullet_state.h"

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