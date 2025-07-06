#include "enemy.h"

CreepEnemy::CreepEnemy(std::shared_ptr<Model> m)
    : stateMachine(this), model(m), direction(glm::vec3(0.0f, 0.0f, 0.0f))
{
}
CreepEnemy::~CreepEnemy()
{
    if (model)
    {
        model->cleanup();
    }
}

void CreepEnemy::update(float deltaTime)
{
    stateMachine.update(deltaTime);
}

void CreepEnemy::changeState(State<EnemyAbstract> *newState)
{
    stateMachine.changeState(newState);
}

void CreepEnemy::updateModelRotation(float deltaTime)
{
    glm::vec3 rotation = model->getRotation();
    if (glm::normalize(rotation) == direction)
    {
        return; 
    }

    float targetAngle = std::atan2(direction.y, direction.x) - glm::radians(90.0f);
    float currentAngle = rotation.z;

    float deltaAngle = targetAngle - currentAngle;
    deltaAngle = std::atan2(std::sin(deltaAngle), std::cos(deltaAngle));

    float maxDelta = rotationSpeed * deltaTime;
    deltaAngle = glm::clamp(deltaAngle, -maxDelta, maxDelta);

    rotation.z = currentAngle + deltaAngle;
    model->setRotation(rotation);
}

void CreepEnemy::move(float deltaTime)
{
    acceleration = direction * accelerationRate;
    velocity += acceleration * deltaTime;

    if (glm::length(velocity) > maxSpeed)
    {
        velocity = glm::normalize(velocity) * maxSpeed;
    }

    glm::vec3 currentPos = model->getPosition();
    glm::vec3 newPos = currentPos + velocity * deltaTime;
    model->setPosition(newPos);
}

void CreepEnemy::draw()
{
    model->draw();
}