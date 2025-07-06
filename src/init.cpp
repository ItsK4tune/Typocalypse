#include "utilities/init.h"
#include "utilities/check_word.h"
#include <iostream>
#include <global.h>

GLFWwindow *createWindow(int width, int height, const char *title)
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return nullptr;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCharCallback(window, character_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    return window;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void character_callback(GLFWwindow *window, unsigned int codepoint)
{
    Global::getInstance().player.currentTypedWord += static_cast<char>(codepoint);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        if (key == GLFW_KEY_BACKSPACE && !Global::getInstance().player.currentTypedWord.empty())
        {
            Global::getInstance().player.currentTypedWord.pop_back();
        }
        else if (key == GLFW_KEY_ENTER || key == GLFW_KEY_SPACE)
        {
            checkWord();
            Global::getInstance().player.currentTypedWord.clear();
        }
    }
}

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    Global::getInstance().game.mouseX = static_cast<int>(xpos);
    Global::getInstance().game.mouseY = static_cast<int>(ypos);
    Global::getInstance().game.isMousePressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
}

void terminate(GLFWwindow *window)
{
    glfwDestroyWindow(window);
    glfwTerminate();
}