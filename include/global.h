#pragma once

#include <string>
#include <vector>

#include "enemy.h"
#include "camera.h"
#include "global_state_machine.h"
#include "enemy_state.h"
#include "bullet.h"
#include "bullet_state.h"

#include "utilities/text_renderer.h"

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
    int maxEnemyCount = 1;
    int currentEnemyCount = 0;

    void clear() { enemies.clear(); }
    void add(std::shared_ptr<CreepEnemy> e) { enemies.push_back(e); }
    void updateCurrentEnemyCount()
    {
        currentEnemyCount = 0;
        for (auto &e : enemies)
        {
            if (e->getStateMachine().getCurrentState() != &EnemyDieState::getInstance())
            {
                currentEnemyCount++;
            }
        }
    }
};

class GameManager
{
public:
    int mouseX = 0;
    int mouseY = 0;
    bool isMousePressed = false;
};

class BulletPool
{
public:
    std::vector<std::shared_ptr<Bullet>> bullets;

    void init(size_t count, std::shared_ptr<Model> model)
    {
        bullets.clear();
        for (size_t i = 0; i < count; ++i)
        {
            auto b = std::make_shared<Bullet>(model);
            bullets.push_back(b);
        }
    }

    Bullet *spawn(const glm::vec3 &pos, const std::shared_ptr<EnemyAbstract> &target)
    {
        for (auto &b : bullets)
        {
            if (b->getStateMachine().getCurrentState() == &BulletDieState::getInstance())
            {
                b->getModel()->setPosition(pos);
                b->setTarget(target);
                b->changeState(&BulletFlyingState::getInstance());
                return b.get();
            }
        }
        return nullptr;
    }

    void updateAll(float dt)
    {
        for (auto &b : bullets)
        {
            if (b->getStateMachine().getCurrentState() != &BulletDieState::getInstance())
                b->update(dt);
        }
    }
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
    BulletPool bulletPool;

    std::shared_ptr<Camera> camera;

    GlobalStateMachine stateMachine;

    std::unique_ptr<TextRenderer> text;

    const int screenWidth = 1920;
    const int screenHeight = 1080;

    void update(float dt)
    {
        stateMachine.update(dt);
        bulletPool.updateAll(dt);
    }
    void changeState(State<Global> *newState) { stateMachine.changeState(newState); }
    void initText()
    {
        text = std::make_unique<TextRenderer>(screenWidth, screenHeight);
        text->load("TimesRegular.ttf", screenWidth / 48);
    }
    void drawText()
    {
        std::string typed = "Play Typocalypse";
        float scale = 1.0f, width = 0.0f;
        const auto &chars = text->getCharacters();
        for (char c : typed)
        {
            if (chars.count(c))
                width += (chars.at(c).advance >> 6) * scale;
        }
        float x = (screenWidth - width) / 2.0f;
        float y = screenHeight / 2.0f;
        text->renderText(typed, x, y, scale, glm::vec3(0.2f, 0.2f, 0.2f));
    }

private:
    Global()
        : camera(std::make_shared<Camera>(
              glm::vec3(0.0f, 0.0f, 3.0f),
              glm::vec3(0.0f, 0.0f, -1.0f),
              glm::vec3(0.0f, 1.0f, 0.0f))),
          stateMachine(this)
    {
    }
};