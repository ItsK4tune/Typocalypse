#pragma once

#include <string>
#include <vector>

#include "camera.h"
#include "global/global_state_machine.h"
#include "pool/creep_enemy_pool.h"
#include "pool/bullet_pool.h"
#include "utilities/text_renderer.h"
#include "global/player_data.h"

class GameAttribute
{
public:
    int health = 100;
    int armor = 50;
    int score = 0;
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
    PlayerData playerData;
    GameManager game;
    CreepEnemyPool enemy;
    BulletPool bulletPool;
    std::shared_ptr<Camera> camera;
    GlobalStateMachine stateMachine;
    std::unique_ptr<TextRenderer> text;

    int screenWidth = 1920;
    int screenHeight = 1080;

    void update(float dt);
    void changeState(State<Global> *newState);
    void initText();
    void drawText();

private:
    Global();
};