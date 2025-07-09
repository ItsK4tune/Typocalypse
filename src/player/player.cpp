#include "player/player.h"

Player::Player(std::shared_ptr<Model> m)
    : model(m), stateMachine(this)
{
    model->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
}

Player::~Player()
{
    if (model)
    {
        model->cleanup();
    }
}

std::shared_ptr<Model> Player::getModel() const { return model; }
PlayerStateMachine &Player::getStateMachine() { return stateMachine; }
const AABB &Player::getLocalAABB() const { return localAABB; }
AABB Player::getWorldAABB() const
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

void Player::setLocalAABB(const AABB &box) { localAABB = box; }

void Player::changeState(State<Player> *newState)
{
    stateMachine.changeState(newState);
}

void Player::update(float deltaTime)
{
    stateMachine.update(deltaTime);
}

void Player::draw()
{
    model->draw();
}