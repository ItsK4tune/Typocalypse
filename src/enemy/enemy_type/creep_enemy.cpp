#include "enemy/enemy.h"
#include "global/global.h"

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

void CreepEnemy::setDirection(const glm::vec3 &dir) { direction = glm::normalize(dir); }
void CreepEnemy::setVelocity(const glm::vec3 &vel) { velocity = vel; }
void CreepEnemy::setAcceleration(const glm::vec3 &acc) { acceleration = acc; }
void CreepEnemy::setMaxSpeed(float speed) { maxSpeed = speed; }
void CreepEnemy::setAccelerationRate(float rate) { accelerationRate = rate; }
void CreepEnemy::setWord(const std::string &w) { word = w; }
void CreepEnemy::setLocalAABB(const AABB &box) { localAABB = box; }

std::shared_ptr<Model> CreepEnemy::getModel() const { return model; }
EnemyStateMachine &CreepEnemy::getStateMachine() { return stateMachine; }
glm::vec3 CreepEnemy::getDirection() const { return direction; }
glm::vec3 CreepEnemy::getVelocity() const { return velocity; }
glm::vec3 CreepEnemy::getAcceleration() const { return acceleration; }
float CreepEnemy::getMaxSpeed() const { return maxSpeed; }
float CreepEnemy::getAccelerationRate() const { return accelerationRate; }
const std::string &CreepEnemy::getWord() const { return word; }
const AABB &CreepEnemy::getLocalAABB() const { return localAABB; }
AABB CreepEnemy::getWorldAABB() const
{
    glm::mat4 modelMat = model->getModelMatrix();
    glm::vec3 corners[8] = {
        localAABB.min,
        glm::vec3(localAABB.min.x, localAABB.min.y, localAABB.max.z),
        glm::vec3(localAABB.min.x, localAABB.max.y, localAABB.min.z),
        glm::vec3(localAABB.min.x, localAABB.max.y, localAABB.max.z),
        glm::vec3(localAABB.max.x, localAABB.min.y, localAABB.min.z),
        glm::vec3(localAABB.max.x, localAABB.min.y, localAABB.max.z),
        glm::vec3(localAABB.max.x, localAABB.max.y, localAABB.min.z),
        localAABB.max};

    glm::vec3 minPt(FLT_MAX), maxPt(-FLT_MAX);
    for (int i = 0; i < 8; ++i)
    {
        glm::vec3 transformed = glm::vec3(modelMat * glm::vec4(corners[i], 1.0f));
        minPt = glm::min(minPt, transformed);
        maxPt = glm::max(maxPt, transformed);
    }

    return AABB(minPt, maxPt);
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