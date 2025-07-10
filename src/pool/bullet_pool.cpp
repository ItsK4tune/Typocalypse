#include <glm/glm.hpp>
#include <iostream>

#include "pool/bullet_pool.h"
#include "bullet/bullet_state.h"
#include "resource_manager/resource_manager.h"
#include "utilities/resource_enum.h"

void BulletPool::init(size_t count)
{
    bullets.clear();
    for (size_t i = 0; i < count; ++i)
    {
        auto bulletModel = std::make_shared<Model>(*ResourceManager::getInstance().getModel(std::to_string(static_cast<int>(ResourceType::Bullet))));
        bulletModel->setShader(ResourceManager::getInstance().getShader(std::to_string(static_cast<int>(ShaderType::Default))));
        auto b = std::make_shared<Bullet>(bulletModel);
        b->setLocalAABB(bulletModel->getAABB());
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