#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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

    virtual std::shared_ptr<Model> getModel() const = 0;
    virtual EnemyStateMachine &getStateMachine() = 0;
    virtual glm::vec3 getDirection() const = 0;
    virtual glm::vec3 getVelocity() const = 0;
    virtual glm::vec3 getAcceleration() const = 0;
    virtual float getMaxSpeed() const = 0;
    virtual float getAccelerationRate() const = 0;

    // state machine
    virtual void update(float deltaTime) = 0;
    virtual void changeState(State<EnemyAbstract> *newState) = 0;

    // movement methods
    virtual void updateModelRotation(float deltaTime) = 0;
    virtual void move(float deltaTime) = 0;
    virtual void draw() = 0;
};

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

    std::shared_ptr<Model> getModel() const override { return model; }
    EnemyStateMachine &getStateMachine() override { return stateMachine; }
    glm::vec3 getDirection() const override { return direction; }
    glm::vec3 getVelocity() const override { return velocity; }
    glm::vec3 getAcceleration() const override { return acceleration; }
    float getMaxSpeed() const override { return maxSpeed; }
    float getAccelerationRate() const override { return accelerationRate; }

    // State machine
    void update(float deltaTime) override;
    void changeState(State<EnemyAbstract> *newState) override;

    // Movement methods
    void updateModelRotation(float deltaTime) override;
    void move(float deltaTime) override;
    void draw() override;

private:
    EnemyStateMachine stateMachine;
    std::shared_ptr<Model> model;
    glm::vec3 direction;
    glm::vec3 velocity = glm::vec3(0.0f);
    glm::vec3 acceleration = glm::vec3(0.0f);
    float maxSpeed = 1.0f;
    float accelerationRate = 5.0f;
    float rotationSpeed = glm::radians(1440.0f);
};
