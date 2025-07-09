#pragma once

#include "enemy/enemy_abstract.h"

struct ChargeStats : public EnemyStats
{
    ChargeStats() {
        numberOfUnique = 1;
    }

    float chargeTime = 5.0f;
    float triggerTime = 1.0f;

    void reset() override
    {
        EnemyStats::reset();
        numberOfUnique = 1;
        chargeTime = 5.0f;
        triggerTime = 1.0f;
    }
};

class ChargeEnemy : public EnemyAbstract
{
public:
    ChargeEnemy(std::shared_ptr<Model> m);
    ~ChargeEnemy() override;

    void setDirection(const glm::vec3 &dir) override;
    void setWord(const std::string &w) override;
    void setLocalAABB(const AABB &box) override;

    std::shared_ptr<Model> getModel() const override;
    EnemyStateMachine &getStateMachine() override;
    glm::vec3 getDirection() const override;
    const std::string &getWord() const override;
    const AABB &getLocalAABB() const override;
    AABB getWorldAABB() const override;

    // State machine
    void update(float deltaTime) override;
    void changeState(State<EnemyAbstract> *newState) override;

    // Movement methods
    void updateModelRotation(float deltaTime) override;
    void move(float deltaTime) override;
    // void changeWord(const std::vector<std::string>& wordList) override;
    void draw() override;
    void drawText() override;

    void uniqueTrigger(float deltaTime) override;
    bool uniqueMove(float deltaTime) override;
    EnemyStats *getStats() override { return &stats; }

private:
    ChargeStats stats;
    glm::vec3 direction;
    float rotationSpeed = glm::radians(1440.0f);
    std::string word = "Charge";

    EnemyStateMachine stateMachine;
    std::shared_ptr<Model> model;
    AABB localAABB;

    bool charge(float deltaTime);
    bool trigger(float deltaTime);
};