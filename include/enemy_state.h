#pragma once

#include "state.h"
#include "enemy.h"
#include <iostream>

class EnemyIdleState : public State<EnemyAbstract>
{
public:
    static EnemyIdleState &getInstance()
    {
        static EnemyIdleState instance;
        return instance;
    }

    void enter(EnemyAbstract *enemy) override
    {
        std::cout << "[EnemyIdleState] Enter: enemy idling\n";
    }

    void update(EnemyAbstract *enemy, float deltaTime) override
    {
        enemy->setVelocity(glm::vec3(0.0f));
        enemy->setAcceleration(glm::vec3(0.0f));
    }

    void exit(EnemyAbstract *enemy) override
    {
        std::cout << "[EnemyIdleState] Exit: enemy stop idling\n";
    }

private:
    EnemyIdleState() {}
};

class EnemyMoveState : public State<EnemyAbstract>
{
public:
    static EnemyMoveState &getInstance()
    {
        static EnemyMoveState instance;
        return instance;
    }

    void enter(EnemyAbstract *enemy) override
    {
        std::cout << "[EnemyMoveState] Enter: enemy starts moving\n";
    }

    void update(EnemyAbstract *enemy, float deltaTime) override
    {
        enemy->move(deltaTime);
    }

    void exit(EnemyAbstract *enemy) override
    {
        std::cout << "[EnemyMoveState] Exit: enemy stops moving\n";
    }

private:
    EnemyMoveState() {}
};

class EnemyRunAwayState : public State<EnemyAbstract>
{
public:
    static EnemyRunAwayState &getInstance()
    {
        static EnemyRunAwayState instance;
        return instance;
    }

    void enter(EnemyAbstract *enemy) override
    {
        std::cout << "[EnemyRunAwayState] Enter: enemy starts running away\n";
    }

    void update(EnemyAbstract *enemy, float deltaTime) override
    {
        enemy->move(deltaTime);
    }

    void exit(EnemyAbstract *enemy) override
    {
        std::cout << "[EnemyRunAwayState] Exit: enemy stops running away\n";
    }

private:
    EnemyRunAwayState() {}
};
