#pragma once

#include "enemy/enemy_abstract.h"

class CreepEnemy : public EnemyAbstract
{
public:
    CreepEnemy(std::shared_ptr<Model> m);
    ~CreepEnemy() override;

    void setDirection(const glm::vec3 &dir) override { direction = glm::normalize(dir); }
    void setVelocity(const glm::vec3 &vel) override { velocity = vel; }
    void setAcceleration(const glm::vec3 &acc) override { acceleration = acc; }
    void setMaxSpeed(float speed) override { maxSpeed = speed; }
    void setAccelerationRate(float rate) override { accelerationRate = rate; }
    void setWord(const std::string &w) override { word = w; }
    void setLocalAABB(const AABB &box) override { localAABB = box; }

    std::shared_ptr<Model> getModel() const override { return model; }
    EnemyStateMachine &getStateMachine() override { return stateMachine; }
    glm::vec3 getDirection() const override { return direction; }
    glm::vec3 getVelocity() const override { return velocity; }
    glm::vec3 getAcceleration() const override { return acceleration; }
    float getMaxSpeed() const override { return maxSpeed; }
    float getAccelerationRate() const override { return accelerationRate; }
    const std::string &getWord() const override { return word; }
    const AABB &getLocalAABB() const override { return localAABB; }
    AABB getWorldAABB() const override
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

    // State machine
    void update(float deltaTime) override;
    void changeState(State<EnemyAbstract> *newState) override;

    // Movement methods
    void updateModelRotation(float deltaTime) override;
    void move(float deltaTime) override;
    //void changeWord(const std::vector<std::string>& wordList) override;
    void draw() override;
    void drawText() override;

private:
    EnemyStateMachine stateMachine;
    std::shared_ptr<Model> model;
    glm::vec3 direction;
    glm::vec3 velocity = glm::vec3(0.0f);
    glm::vec3 acceleration = glm::vec3(0.0f);
    float maxSpeed = 0.5f;
    float accelerationRate = 3.0f;
    float rotationSpeed = glm::radians(1440.0f);
    std::string word = "Creep";
    AABB localAABB;
};