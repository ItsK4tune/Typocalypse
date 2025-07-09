#include "menu/menu.h"
#include <iostream>
#include <algorithm>

Menu::Menu()
    : stateMachine(this), textRenderer(nullptr) {}
Menu::Menu(std::shared_ptr<TextRenderer> renderer)
    : stateMachine(this), textRenderer(renderer) {}

void Menu::addItem(const std::string &text,
                   const glm::vec2 &pos,
                   float scale,
                   const glm::vec3 &color)
{
    items.emplace_back(text, pos, scale, color);
}

void Menu::setItem(size_t index,
                   const glm::vec2 &pos,
                   float scale,
                   const glm::vec3 &color)
{
    if (index >= items.size())
    {
        std::cerr << "[Menu] Invalid item index: " << index << "\n";
        return;
    }

    items[index].position = pos;
    items[index].baseScale = scale;
    items[index].baseColor = color;
}

void Menu::setTextRenderer(std::shared_ptr<TextRenderer> text) {
    textRenderer = text;
}

void Menu::clear()
{
    items.clear();
    selectedIndex = 0;
}

void Menu::moveUp()
{
    if (!items.empty())
        selectedIndex = (selectedIndex - 1 + items.size()) % items.size();
}

void Menu::moveDown()
{
    if (!items.empty())
        selectedIndex = (selectedIndex + 1) % items.size();
}

int Menu::getSelectedIndex() const
{
    return selectedIndex;
}

void Menu::render()
{
    for (size_t i = 0; i < items.size(); ++i)
    {
        const MenuItem &item = items[i];
        float scale = item.baseScale;
        glm::vec3 color = item.baseColor;

        if ((int)i == selectedIndex)
        {
            scale += hoverScaleBoost;
            color = selectedColor;
        }

        textRenderer->renderText(item.text, item.position.x, item.position.y, scale, color);
    }
}

void Menu::update(float deltaTime)
{
    stateMachine.update(deltaTime);
}

void Menu::changeState(State<Menu> *newState)
{
    stateMachine.changeState(newState);
}

MenuStateMachine &Menu::getStateMachine()
{
    return stateMachine;
}
