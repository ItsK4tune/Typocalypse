#include "bullet/bullet_state.h"

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