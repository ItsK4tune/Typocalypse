#pragma once

#include "state.h"
#include "enemy.h"
#include <iostream>

class EnemyIdleState : public State<Enemy> {
public:
    static EnemyIdleState& getInstance() {
        static EnemyIdleState instance;
        return instance;
    }

    void enter(Enemy* enemy) override {
        std::cout << "[EnemyIdleState] Enter: enemy idling\n";
    }

    void update(Enemy* enemy, float deltaTime) override {
		return; // No movement in idle state
    }

    void exit(Enemy* enemy) override {
        std::cout << "[EnemyIdleState] Exit: enemy stop idling\n";
    }

private:
    EnemyIdleState() {}
};

class EnemyMoveState : public State<Enemy> {
public:
    static EnemyMoveState& getInstance() {
        static EnemyMoveState instance;
        return instance;
    }

    void enter(Enemy* enemy) override {
        std::cout << "[EnemyMoveState] Enter: enemy starts moving\n";
    }

    void update(Enemy* enemy, float deltaTime) override {
        enemy->move(deltaTime);
    }

    void exit(Enemy* enemy) override {
        std::cout << "[EnemyMoveState] Exit: enemy stops moving\n";
    }

private:
    EnemyMoveState() {}
};
