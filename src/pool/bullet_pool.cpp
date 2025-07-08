#include <glm/glm.hpp>
#include <iostream>

#include "pool/bullet_pool.h"
#include "bullet/bullet_state.h"
#include "utilities/genMesh.h"

void BulletPool::init(size_t count, const Shader &shader)
{
    AABB localAABB = initRectangleMesh();
    bullets.clear();
    for (size_t i = 0; i < count; ++i)
    {
        auto bulletModel = std::make_shared<Model>(bulletVertices, bulletIndices);
        bulletModel->setShader(std::make_shared<Shader>(shader));
        auto b = std::make_shared<Bullet>(bulletModel);
        b->setLocalAABB(localAABB);
        bullets.push_back(b);
    }
}

Bullet *BulletPool::spawn(const glm::vec3 &pos, const std::shared_ptr<EnemyAbstract> &target)
{
    for (auto &b : bullets)
    {
        if (b->getStateMachine().getCurrentState() == &BulletDieState::getInstance())
        {
            b->getModel()->setPosition(pos);
            b->setTarget(target);
            b->changeState(&BulletFlyingState::getInstance());
            return b.get();
        }
    }
    return nullptr;
}

void BulletPool::clear()
{
    bullets.clear();
    bulletVertices.reset();
    bulletIndices.reset();
}

AABB BulletPool::initRectangleMesh()
{
    generateRectangleMesh(bulletVertices, bulletIndices, 0.07f, 0.07f, glm::vec3(0.0f));

    if (!bulletVertices || bulletVertices->empty())
    {
        std::cerr << "[BulletPool::initRectangleMesh] bulletVertices is empty!\n";
        return AABB();
    }

    glm::vec3 min = bulletVertices->at(0).position;
    glm::vec3 max = min;

    for (size_t i = 1; i < bulletVertices->size(); ++i)
    {
        const glm::vec3 &pos = bulletVertices->at(i).position;
        min = glm::min(min, pos);
        max = glm::max(max, pos);
    }

    return AABB(min, max);
}