#include "global/global.h"

Global::Global()
    : camera(std::make_shared<Camera>(
          glm::vec3(0.0f, 0.0f, 3.0f),
          glm::vec3(0.0f, 0.0f, -1.0f),
          glm::vec3(0.0f, 1.0f, 0.0f))),
      stateMachine(this)
{
}

void Global::update(float dt)
{
    stateMachine.update(dt);
}
void Global::changeState(State<Global> *newState)
{
    stateMachine.changeState(newState);
}
void Global::initText()
{
    fontMap[FontSize::Title] = std::make_shared<TextRenderer>(screenWidth, screenHeight);
    fontMap[FontSize::Title]->load("TimesRegular.ttf", toInt(FontSize::Title));

    fontMap[FontSize::Menu] = std::make_shared<TextRenderer>(screenWidth, screenHeight);
    fontMap[FontSize::Menu]->load("TimesRegular.ttf", toInt(FontSize::Menu));

    fontMap[FontSize::Normal] = std::make_shared<TextRenderer>(screenWidth, screenHeight);
    fontMap[FontSize::Normal]->load("TimesRegular.ttf", toInt(FontSize::Normal));

    menu = std::make_shared<Menu>(fontMap[FontSize::Menu]);
}
void Global::createPool()
{
    for (auto &e : creepEnemyPool.enemies)
        enemies.push_back(e);

    for (auto &e : chargeEnemyPool.enemies)
        enemies.push_back(e);
}