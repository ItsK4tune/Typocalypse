#pragma once

#include <memory>
#include <string>
#include <glm/glm.hpp>

#include "utilities/AABB.h"
#include "model.h"
#include "enemy_state_machine.h"

class EnemyAbstract
{
public:
    virtual ~EnemyAbstract() = default;

    // Setters and Getters
    virtual void setDirection(const glm::vec3 &dir) = 0;
    virtual void setVelocity(const glm::vec3 &vel) = 0;
    virtual void setAcceleration(const glm::vec3 &acc) = 0;
    virtual void setMaxSpeed(float speed) = 0;
    virtual void setAccelerationRate(float rate) = 0;
    virtual void setWord(const std::string &w) = 0;
    virtual const std::string &getWord() const = 0;
    virtual void setLocalAABB(const AABB &box) = 0;

    virtual std::shared_ptr<Model> getModel() const = 0;
    virtual EnemyStateMachine &getStateMachine() = 0;
    virtual glm::vec3 getDirection() const = 0;
    virtual glm::vec3 getVelocity() const = 0;
    virtual glm::vec3 getAcceleration() const = 0;
    virtual float getMaxSpeed() const = 0;
    virtual float getAccelerationRate() const = 0;
    virtual const AABB &getLocalAABB() const = 0;
    virtual AABB getWorldAABB() const = 0;

    // state machine
    virtual void update(float deltaTime) = 0;
    virtual void changeState(State<EnemyAbstract> *newState) = 0;

    // movement methods
    virtual void updateModelRotation(float deltaTime) = 0;
    virtual void move(float deltaTime) = 0;
    // virtual void changeWord(const std::vector<std::string>& wordList) = 0;
    virtual void draw() = 0;
    virtual void drawText() = 0;
};