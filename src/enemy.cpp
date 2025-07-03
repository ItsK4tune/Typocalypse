#include "enemy.h"

void Enemy::updateDirection(float deltaTime, glm::vec3 playerPosition)
{
    glm::vec3 currentPos = model->getPosition();
    direction = glm::normalize(playerPosition - currentPos);
}

void Enemy::move(float deltaTime)
{
    glm::vec3 currentPos = model->getPosition();
    glm::vec3 newPos = currentPos + direction * speed * deltaTime;
    model->setPosition(newPos);
}

void Enemy::draw()
{
    model->draw();
}