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
    text = std::make_unique<TextRenderer>(screenWidth, screenHeight);
    text->load("TimesRegular.ttf", screenWidth / 48);
}
void Global::drawText()
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