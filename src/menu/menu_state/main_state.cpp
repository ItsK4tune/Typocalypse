#include "menu/menu_state.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "global/global.h"

MenuMainState::MenuMainState() {}

MenuMainState &MenuMainState::getInstance()
{
    static MenuMainState instance;
    return instance;
}

void MenuMainState::enter(Menu *menu)
{
    menu->clearTexts();

    float xStart = Global::getInstance().screenHeight * 0.2;
    float yStart = Global::getInstance().screenHeight * 0.1;
    float gap = 80.0f;

    menu->addTextItem("Play", glm::vec2(xStart, yStart + 0 * gap), 1.0f, glm::vec3(0.0f));
    menu->addTextItem("Settings", glm::vec2(xStart, yStart + 1 * gap), 1.0f, glm::vec3(0.0f));
    menu->addTextItem("Exit", glm::vec2(xStart, yStart + 2 * gap), 1.0f, glm::vec3(0.0f));
}

void MenuMainState::update(Menu *menu, float deltaTime)
{
    if (glfwGetKey(Global::getInstance().window, GLFW_KEY_UP) == GLFW_PRESS)
        menu->moveUp();

    if (glfwGetKey(Global::getInstance().window, GLFW_KEY_DOWN) == GLFW_PRESS)
        menu->moveDown();

    menu->render();
}

void MenuMainState::exit(Menu *menu)
{
    // Có thể fade out hoặc cleanup nếu muốn
}