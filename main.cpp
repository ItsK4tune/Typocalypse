#include <memory>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <ctime>

#include "camera.h"
#include "model.h"
#include "enemy/enemy.h"
#include "enemy/enemy_state.h"
#include "global/global.h"
#include "global/global_state.h"
#include "bullet/bullet_state.h"
#include "player/player.h"
#include "resource_manager/resource_manager.h"

#include "utilities/init.h"
#include "utilities/text_renderer.h"
#include "utilities/AABB.h"

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    Global::getInstance().window = createWindow(Global::getInstance().screenWidth, Global::getInstance().screenHeight, "Typocalypse");
    ResourceManager::getInstance().loadFromFile("resource.rm");
    Global::getInstance().initText();

    float lastTime = glfwGetTime();
    float lastFrame = glfwGetTime();
    int frames = 0;

    float totalTime = 0.0f;
    while (!glfwWindowShouldClose(Global::getInstance().window))
    {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // FPS counter
        frames++;
        if (currentFrame - lastTime >= 1.0)
        {
            std::stringstream ss;
            ss << "Typocalypse - FPS: " << frames;
            glfwSetWindowTitle(Global::getInstance().window, ss.str().c_str());
            frames = 0;
            lastTime += 1.0;
        }

        // Clear screen
        glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if (glfwGetKey(Global::getInstance().window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(Global::getInstance().window, true);

        Global::getInstance().update(deltaTime);
        // if (Global::getInstance().stateMachine.getCurrentState() == &GlobalMenuState::getInstance())

        if (Global::getInstance().stateMachine.getCurrentState() == &GlobalGameOverState::getInstance())
        {
            glfwSetWindowShouldClose(Global::getInstance().window, true);
        }

        glfwSwapBuffers(Global::getInstance().window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}