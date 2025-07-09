#pragma once

#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "menu/menu.h"
#include "camera.h"
#include "global/global_state_machine.h"
#include "pool/creep_enemy_pool.h"
#include "pool/charge_enemy_pool.h"
#include "pool/bullet_pool.h"
#include "utilities/text_renderer.h"
#include "global/player_data.h"
#include "utilities/font_size.h"

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

    GLFWwindow *window;
    std::shared_ptr<Menu> menu;

    GameAttribute attribute;
    PlayerData playerData;
    GameManager game;
    std::shared_ptr<Camera> camera;

    std::vector<std::shared_ptr<EnemyAbstract>> enemies;
    CreepEnemyPool creepEnemyPool;
    ChargeEnemyPool chargeEnemyPool;
    BulletPool bulletPool;

    GlobalStateMachine stateMachine;
    std::map<FontSize, std::shared_ptr<TextRenderer>> fontMap;

    int screenWidth = 1920;
    int screenHeight = 1080;

    void update(float dt);
    void changeState(State<Global> *newState);
    void initText();
    void createPool();

private:
    Global();
};