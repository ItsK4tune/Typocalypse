#pragma once

#include <memory>
#include <string>
#include <glm/glm.hpp>
#include "bullet_state_machine.h"
#include "model.h"
#include "enemy/enemy.h"

#include "utilities/AABB.h"

class Bullet
{
public:
    Bullet(std::shared_ptr<Model> m);
    ~Bullet();

    void setDirection(const glm::vec3 &dir);
    void setTarget(std::shared_ptr<EnemyAbstract> e) { target = e; }
    void setVelocity(const glm::vec3 &v) { velocity = v; }
    void setAcceleration(const glm::vec3 &a) { acceleration = a; }
    void setMaxSpeed(float s) { maxSpeed = s; }
    void setLocalAABB(const AABB &box) { localAABB = box; }

    BulletStateMachine &getStateMachine() { return stateMachine; }
    std::shared_ptr<Model> getModel() const { return model; }
    std::shared_ptr<EnemyAbstract> getTarget() const { return target; }
    const AABB &getLocalAABB() const { return localAABB; }
    AABB getWorldAABB() const
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

    void update(float deltaTime);
    void changeState(State<Bullet> *newState);
    void draw();
    void move(float deltaTime);

private:
    std::shared_ptr<Model> model;
    glm::vec3 direction;
    glm::vec3 velocity = glm::vec3(0.0f);
    glm::vec3 acceleration = glm::vec3(0.0f);
    float maxSpeed = 0.1f;
    float accelerationRate = 0.1f;
    AABB localAABB;

    BulletStateMachine stateMachine;

    std::shared_ptr<EnemyAbstract> target;
};