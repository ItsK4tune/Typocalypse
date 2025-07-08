#include "enemy.h"
#include "global.h"

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

//void CreepEnemy::changeWord(const std::vector<std::string> &wordList)

void CreepEnemy::draw()
{
    model->draw();
}

void CreepEnemy::drawText()
{
    glm::vec3 pos = model->getPosition();
    glm::vec4 clipSpace = Global::getInstance().camera->getPerspectiveProjection(45.0f, (float)Global::getInstance().screenWidth / Global::getInstance().screenHeight, 0.1f, 100.0f) *
                          Global::getInstance().camera->getViewMatrix() * glm::vec4(pos, 1.0f);
    if (clipSpace.w > 0.0f)
    {
        glm::vec3 ndc = glm::vec3(clipSpace) / clipSpace.w;
        float scale = 0.7f, wordWidth = 0.0f;
        const auto &chars = Global::getInstance().text->getCharacters();
        for (char c : word)
        {
            if (chars.count(c))
                wordWidth += (chars.at(c).advance >> 6) * scale;
        }
        float x = (ndc.x * 0.5f + 0.5f) * Global::getInstance().screenWidth - wordWidth / 2.0f;
        float y = (ndc.y * 0.5f + 0.5f) * Global::getInstance().screenHeight - 50.0f;

        Global::getInstance().text->renderText(word, x, y, scale, glm::vec3(0.1f, 0.1f, 0.1f));
    }
}