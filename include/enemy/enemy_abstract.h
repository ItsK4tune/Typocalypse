#pragma once

#include <memory>
#include <string>
#include <glm/glm.hpp>

#include "utilities/AABB.h"
#include "model.h"
#include "enemy_state_machine.h"

struct EnemyStats {
    glm::vec3 velocity = glm::vec3(0.0f);
    glm::vec3 acceleration = glm::vec3(0.0f);
    float maxSpeed = 0.5f;
    float accelerationRate = 3.0f;
    int numberOfUnique = 0;

    virtual void reset() {
        velocity = glm::vec3(0.0f);
        acceleration = glm::vec3(0.0f);
        maxSpeed = 0.5f;
        accelerationRate = 3.0f;
        int numberOfUnique = 0;
    }

    virtual ~EnemyStats() = default;
};

class EnemyAbstract
{
public:
    virtual ~EnemyAbstract() = default;

    // Setters and Getters
    virtual void setDirection(const glm::vec3 &dir) = 0;
    virtual void setWord(const std::string &w) = 0;
    virtual const std::string &getWord() const = 0;
    virtual void setLocalAABB(const AABB &box) = 0;

    virtual std::shared_ptr<Model> getModel() const = 0;
    virtual EnemyStateMachine &getStateMachine() = 0;
    virtual glm::vec3 getDirection() const = 0;
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

    virtual void uniqueTrigger(float deltaTime) = 0;
    virtual bool uniqueMove(float deltaTime) = 0; 
    virtual EnemyStats* getStats() = 0;
};