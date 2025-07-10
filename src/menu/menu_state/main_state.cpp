#include "menu/menu_state.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "global/global.h"
#include "resource_manager/resource_manager.h"
#include "utilities/resource_enum.h"

MenuMainState::MenuMainState() {}

MenuMainState &MenuMainState::getInstance()
{
    static MenuMainState instance;
    return instance;
}

void MenuMainState::enter(Menu *menu)
{
    menu->clearTexts();
    menu->clearModels();

    float xStart = Global::getInstance().screenHeight * 0.2;
    float yStart = Global::getInstance().screenHeight * 0.1;
    float gap = 80.0f;

    menu->addTextItem("Play", glm::vec2(xStart, yStart + 0 * gap));
    menu->addTextItem("Settings", glm::vec2(xStart, yStart + 1 * gap));
    menu->addTextItem("Exit", glm::vec2(xStart, yStart + 2 * gap));

    auto logoModel = std::make_shared<Model>(*ResourceManager::getInstance().getModel(std::to_string(static_cast<int>(ResourceType::Logo))));
    logoModel->setShader(ResourceManager::getInstance().getShader(std::to_string(static_cast<int>(ShaderType::UI))));
    menu->addModel(logoModel);
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