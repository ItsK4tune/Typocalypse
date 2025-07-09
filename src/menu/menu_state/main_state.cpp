#include "menu/menu_state.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "global/global.h"

MenuMainState::MenuMainState() {}

MenuMainState& MenuMainState::getInstance()
{
    static MenuMainState instance;
    return instance;
}

void MenuMainState::enter(Menu* menu)
{
    menu->clear();

    float xStart = Global::getInstance().screenHeight * 0.2;
    float yStart = Global::getInstance().screenHeight * 0.1;
    float gap = 80.0f;

    menu->addItem("Play",     glm::vec2(xStart, yStart + 0 * gap), 1.0f, glm::vec3(0.0f));
    menu->addItem("Settings", glm::vec2(xStart, yStart + 1 * gap), 1.0f, glm::vec3(0.0f));
    menu->addItem("Exit",     glm::vec2(xStart, yStart + 2 * gap), 1.0f, glm::vec3(0.0f));
}

void MenuMainState::update(Menu* menu, float deltaTime)
{
    // Logic xử lý phím
    if (glfwGetKey(Global::getInstance().window, GLFW_KEY_UP) == GLFW_PRESS)
        menu->moveUp();

    if (glfwGetKey(Global::getInstance().window, GLFW_KEY_DOWN) == GLFW_PRESS)
        menu->moveDown();

    // if (glfwGetKey(Global::getInstance().window, GLFW_KEY_ENTER) == GLFW_PRESS)
    // {
    //     int selected = menu->getSelectedIndex();
    //     if (selected == 0)
    //         // Global::getInstance().changeState(PlayState::getInstance()); // Ví dụ
    //     else if (selected == 1)
    //         std::cout << "Settings...\n";
    //     else if (selected == 2)
    //         exit(0);
    // }

    // Vẽ menu
    menu->render();
}

void MenuMainState::exit(Menu* menu)
{
    // Có thể fade out hoặc cleanup nếu muốn
}