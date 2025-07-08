#include "pool/bullet_pool.h"
#include "bullet/bullet_state.h"
#include "utilities/genMesh.h"

BulletPool::~BulletPool(){
    delete bulletVertices;
    delete bulletIndices;
}

void BulletPool::init(size_t count, const Shader &shader)
{
    AABB localAABB = initRectangleMesh();
    bullets.clear();
    for (size_t i = 0; i < count; ++i)
    {
        auto bulletModel = std::make_shared<Model>(bulletVertices, bulletVertexCount, bulletIndices, bulletIndexCount);
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

AABB BulletPool::initRectangleMesh()
    {
        generateRectangleMesh(bulletVertices, bulletIndices, bulletVertexCount, bulletIndexCount, 0.07f, 0.07f, glm::vec3(0.0f));
        glm::vec3 min = bulletVertices[0].position;
        glm::vec3 max = bulletVertices[0].position;
        for (unsigned int i = 1; i < bulletVertexCount; ++i)
        {
            min = glm::min(min, bulletVertices[i].position);
            max = glm::max(max, bulletVertices[i].position);
        }

        return AABB(min, max);
    }