#include "enemy.h"

Enemy::Enemy(std::shared_ptr<Model> m)
    : stateMachine(this), model(m), direction(glm::vec3(0.0f, 0.0f, 0.0f)), speed(0.1f)
{
}

void Enemy::update(float deltaTime) {
    stateMachine.update(deltaTime);
}

void Enemy::changeState(State<Enemy>* newState) {
    stateMachine.changeState(newState);
}

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