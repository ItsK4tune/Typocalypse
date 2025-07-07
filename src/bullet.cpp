#include "bullet.h"

Bullet::Bullet(std::shared_ptr<Model> m)
    : stateMachine(this), model(m), direction(glm::vec3(0.0f, 0.0f, 0.0f))
{
}
Bullet::~Bullet()
{
    if (model)
    {
        model->cleanup();
    }
}

void Bullet::update(float deltaTime)
{
    stateMachine.update(deltaTime);
}

void Bullet::changeState(State<Bullet> *newState)
{
    stateMachine.changeState(newState);
}

void Bullet::draw()
{
    model->draw();
}

void Bullet::move()
{
    if (!target || !model)
        return;

    glm::vec3 toTarget = target->getModel()->getPosition() - model->getPosition();
    direction = glm::normalize(toTarget);

    acceleration = direction * accelerationRate;

    velocity += acceleration;

    float speed = glm::length(velocity);
    if (speed > maxSpeed)
        velocity = glm::normalize(velocity) * maxSpeed;

    glm::vec3 newPos = model->getPosition() + velocity;
    model->setPosition(newPos);
}
