#include "display/display.h"
#include <iostream>
#include <algorithm>

#include "global/global.h"

Display::Display() : stateMachine(this), textRenderer(nullptr) {}
Display::Display(std::shared_ptr<TextRenderer> renderer) : stateMachine(this), textRenderer(renderer) {}

void Display::addTextItem(const std::string &text,
                          const glm::vec2 &pos,
                          float scale,
                          const glm::vec4 &color)
{
    textItems.emplace_back(text, pos, scale, color);
}

void Display::setTextItem(size_t index,
                          const glm::vec2 &pos,
                          float scale,
                          const glm::vec4 &color)
{
    if (index >= textItems.size())
    {
        std::cerr << "[Display] Invalid item index: " << index << "\n";
        return;
    }

    textItems[index].position = pos;
    textItems[index].baseScale = scale;
    textItems[index].baseColor = color;
}

void Display::clearTexts()
{
    textItems.clear();
    selectedIndex = 0;
}

void Display::addModel(std::shared_ptr<Model> model)
{
    uiModels.push_back(model);
}

void Display::clearModels()
{
    uiModels.clear();
}

void Display::setTextRenderer(std::shared_ptr<TextRenderer> text)
{
    textRenderer = text;
}

void Display::moveUp()
{
    if (!textItems.empty())
        selectedIndex = (selectedIndex - 1 + textItems.size()) % textItems.size();
}

void Display::moveDown()
{
    if (!textItems.empty())
        selectedIndex = (selectedIndex + 1) % textItems.size();
}

int Display::getSelectedIndex() const
{
    return selectedIndex;
}

void Display::render()
{
    for (auto &model : uiModels)
    {
        model->getShader()->use();

        glm::mat4 projection = Global::getInstance().camera->getOrthoProjection(
            0.0f,
            static_cast<float>(Global::getInstance().screenWidth),
            0.0f,
            static_cast<float>(Global::getInstance().screenHeight),
            -1.0f,
            1.0f);

        glm::mat4 mvp = projection * model->getModelMatrix();
        model->getShader()->setMat4("mvp", glm::value_ptr(mvp));
        model->draw();
    }

    for (size_t i = 0; i < textItems.size(); ++i)
    {
        const DisplayItem &item = textItems[i];
        float scale = item.baseScale;
        glm::vec4 color = item.baseColor;

        if ((int)i == selectedIndex)
        {
            scale += hoverScaleBoost;
            color = selectedColor;
        }

        textRenderer->renderText(item.text, item.position.x, item.position.y, scale, color);
    }
}

void Display::update(float deltaTime)
{
    stateMachine.update(deltaTime);
}

void Display::changeState(State<Display> *newState)
{
    stateMachine.changeState(newState);
}

DisplayStateMachine &Display::getStateMachine()
{
    return stateMachine;
}
