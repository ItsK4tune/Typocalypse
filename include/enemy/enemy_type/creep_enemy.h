#pragma once

#include "enemy/enemy_abstract.h"

class CreepEnemy : public EnemyAbstract
{
public:
    CreepEnemy(std::shared_ptr<Model> m);
    ~CreepEnemy() override;

    void setDirection(const glm::vec3 &dir) override;
    void setVelocity(const glm::vec3 &vel) override;
    void setAcceleration(const glm::vec3 &acc) override;
    void setMaxSpeed(float speed) override;
    void setAccelerationRate(float rate) override;
    void setWord(const std::string &w) override;
    void setLocalAABB(const AABB &box) override;

    std::shared_ptr<Model> getModel() const override;
    EnemyStateMachine &getStateMachine() override;
    glm::vec3 getDirection() const override;
    glm::vec3 getVelocity() const override;
    glm::vec3 getAcceleration() const override;
    float getMaxSpeed() const override;
    float getAccelerationRate() const override;
    const std::string &getWord() const override;
    const AABB &getLocalAABB() const override;
    AABB getWorldAABB() const override;

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
    AABB localAABB;
    std::string word = "Creep";
};