#pragma once

#include "enemy/enemy_abstract.h"

struct CreepStats : public EnemyStats
{
    void reset() override
    {
        EnemyStats::reset();
    }
};

class CreepEnemy : public EnemyAbstract
{
public:
    CreepEnemy(std::shared_ptr<Model> m);
    ~CreepEnemy() override;

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

    void uniqueTrigger(float deltaTime) override {}
    bool uniqueMove(float deltaTime) override { return false; }
    EnemyStats *getStats() override { return &stats; }

private:
    CreepStats stats;
    glm::vec3 direction;
    float rotationSpeed = glm::radians(1440.0f);
    std::string word = "Creep";

    EnemyStateMachine stateMachine;
    std::shared_ptr<Model> model;
    AABB localAABB;
};