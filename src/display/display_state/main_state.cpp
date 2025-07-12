#include "display/display_state.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "global/global.h"
#include "resource_manager/resource_manager.h"
#include "utilities/resource_enum.h"

DisplayMainState::DisplayMainState() {}

DisplayMainState &DisplayMainState::getInstance()
{
    static DisplayMainState instance;
    return instance;
}

void DisplayMainState::enter(Display *display)
{
    display->clearTexts();
    display->clearModels();

    float xStart = Global::getInstance().screenHeight * 0.2;
    float yStart = Global::getInstance().screenHeight * 0.1;
    float gap = 80.0f;

    display->addTextItem("Play", glm::vec2(xStart, yStart + 0 * gap));
    display->addTextItem("Settings", glm::vec2(xStart, yStart + 1 * gap));
    display->addTextItem("Exit", glm::vec2(xStart, yStart + 2 * gap));

    auto logoModel = std::make_shared<Model>(*ResourceManager::getInstance().getModel(std::to_string(static_cast<int>(ResourceType::Logo))));
    logoModel->setShader(ResourceManager::getInstance().getShader(std::to_string(static_cast<int>(ShaderType::UI))));
    display->addModel(logoModel);
}

void DisplayMainState::update(Display *display, float deltaTime)
{
    if (glfwGetKey(Global::getInstance().window, GLFW_KEY_UP) == GLFW_PRESS)
        display->moveUp();

    if (glfwGetKey(Global::getInstance().window, GLFW_KEY_DOWN) == GLFW_PRESS)
        display->moveDown();

    display->render();
}

void DisplayMainState::exit(Display *display)
{
    // Có thể fade out hoặc cleanup nếu muốn
}