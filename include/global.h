#pragma once

#include <string>
#include <vector>

#include "enemy.h"
#include "camera.h"
#include "global_state_machine.h"

class GameAttribute
{
public:
    int health = 100;
    int armor = 50;
    int score = 0;
};

class PlayerData
{
public:
    glm::vec3 position = glm::vec3(0.0f);
    std::string currentTypedWord;
};

class EnemyManager
{
public:
    std::vector<std::shared_ptr<CreepEnemy>> enemies;
    int numberOfEnemies = 1;

    void clear() { enemies.clear(); }
    void add(std::shared_ptr<CreepEnemy> e) { enemies.push_back(e); }
};

class GameManager
{
public:
    int mouseX = 0;
    int mouseY = 0;
    bool isMousePressed = false;
};

class Global
{
public:
    static Global &getInstance()
    {
        static Global instance;
        return instance;
    }

    Global(const Global &) = delete;
    Global &operator=(const Global &) = delete;

    GameAttribute attribute;
    PlayerData player;
    EnemyManager enemy;
    GameManager game;

    std::shared_ptr<Camera> camera;

    GlobalStateMachine stateMachine;

    const int screenWidth = 1920;
    const int screenHeight = 1080;

    void update(float dt) { stateMachine.update(dt); }
    void changeState(State<Global> *newState) { stateMachine.changeState(newState); }

private:
    Global()
        : camera(std::make_shared<Camera>(
              glm::vec3(0.0f, 0.0f, 3.0f),
              glm::vec3(0.0f, 0.0f, -1.0f),
              glm::vec3(0.0f, 1.0f, 0.0f))),
          stateMachine(this) {}
};