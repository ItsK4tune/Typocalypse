#include "enemy/enemy.h"
#include "global/global.h"
#include "utilities/text_match.h"

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
void CreepEnemy::setWord(const std::string &w) { word = w; }
void CreepEnemy::setLocalAABB(const AABB &box) { localAABB = box; }

std::shared_ptr<Model> CreepEnemy::getModel() const { return model; }
EnemyStateMachine &CreepEnemy::getStateMachine() { return stateMachine; }
glm::vec3 CreepEnemy::getDirection() const { return direction; }
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
    stats.acceleration = direction * stats.accelerationRate;
    stats.velocity += stats.acceleration * deltaTime;

    if (glm::length(stats.velocity) > stats.maxSpeed)
    {
        stats.velocity = glm::normalize(stats.velocity) * stats.maxSpeed;
    }

    glm::vec3 currentPos = model->getPosition();
    glm::vec3 newPos = currentPos + stats.velocity * deltaTime;
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
    if (clipSpace.w <= 0.0f)
        return;

    glm::vec3 ndc = glm::vec3(clipSpace) / clipSpace.w;

    float scale = 0.7f;
    float wordWidth = 0.0f;
    const auto &chars = Global::getInstance().fontMap[FontSize::Normal]->getCharacters();
    for (char c : word)
    {
        if (chars.count(c))
            wordWidth += (chars.at(c).advance >> 6) * scale;
    }

    float x = (ndc.x * 0.5f + 0.5f) * Global::getInstance().screenWidth - wordWidth / 2.0f;
    float y = (ndc.y * 0.5f + 0.5f) * Global::getInstance().screenHeight - 50.0f;

    std::vector<bool> matchMask = getPrefixMatchMaskFromTypedEnd(
        word, Global::getInstance().playerData.currentTypedWord);

    for (size_t i = 0; i < word.size(); ++i)
    {
        char c = word[i];
        if (!chars.count(c)) continue;

        const Character &ch = chars.at(c);

        float xpos = x;
        float ypos = y;

        glm::vec4 color = matchMask[i] ? glm::vec4(0.9f, 0.1f, 0.1f, 1.0f) : glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);

        Global::getInstance().fontMap[FontSize::Normal]->renderText(std::string(1, c), xpos, ypos, scale, color);

        x += (ch.advance >> 6) * scale;
    }
}