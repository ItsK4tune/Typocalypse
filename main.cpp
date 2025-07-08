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

#include "utilities/init.h"
#include "utilities/genMesh.h"
#include "utilities/text_renderer.h"
#include "utilities/spawn_enemy.h"
#include "utilities/AABB.h"

AABB *playerAABB = new AABB(glm::vec3(-0.05f, -0.05f, 0.0f), glm::vec3(0.05f, 0.05f, 0.0f));

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    GLFWwindow *window = createWindow(Global::getInstance().screenWidth, Global::getInstance().screenHeight, "Typocalypse");

    Global::getInstance().initText();

    initTriangleMesh();

    // player
    Vertex *vertices = nullptr;
    GLuint *indices = nullptr;
    unsigned int vertexCount = 0;
    unsigned int indexCount = 0;
    generateCircleMesh(vertices, indices, vertexCount, indexCount, 64, 0.05f);
    auto model = std::make_shared<Model>(vertices, vertexCount, indices, indexCount);
    Shader shader("basic.vert", "basic.frag");
    model->setShader(std::make_shared<Shader>(shader));
    auto player = std::make_shared<Player>(model);

    // enemy
    std::vector<std::string> wordList = {"cat", "dog", "fish", "bird", "mouse", "elephant", "giraffe", "lion", "tiger", "bear",
                                         "zebra", "monkey", "kangaroo", "panda", "rabbit", "fox", "wolf", "deer", "cow", "sheep"};
    initEnemyPool(wordList, shader);

    // bullet
    Shader bulletShader("basic.vert", "basic.frag");
    Global::getInstance().bulletPool.init(20, bulletShader);

    float lastTime = glfwGetTime();
    float lastFrame = glfwGetTime();
    int frames = 0;

    float totalTime = 0.0f;
    while (!glfwWindowShouldClose(window))
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
            glfwSetWindowTitle(window, ss.str().c_str());
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

        Global::getInstance().update(deltaTime);
        if (Global::getInstance().stateMachine.getCurrentState() == &GlobalMenuState::getInstance())
        {
            glfwSwapBuffers(window);
            glfwPollEvents();
            continue;
        }

        // Set matrices
        glm::mat4 projection = Global::getInstance().camera->getPerspectiveProjection(45.0f, (float)Global::getInstance().screenWidth / Global::getInstance().screenHeight, 0.1f, 100.0f);
        glm::mat4 view = Global::getInstance().camera->getViewMatrix();

        // Draw player
        glm::mat4 mvp = projection * view * player->getModel()->getModelMatrix();
        player->getModel()->getShader()->use();
        player->getModel()->getShader()->setMat4("mvp", glm::value_ptr(mvp));
        player->update(deltaTime);

        for (auto &b : Global::getInstance().bulletPool.bullets)
        {
            if (b->getStateMachine().getCurrentState() == &BulletFlyingState::getInstance())
            {
                b->getModel()->getShader()->use();
                b->getModel()->getShader()->setMat4("mvp", glm::value_ptr(projection * view * b->getModel()->getModelMatrix()));

                if (b->getWorldAABB().intersects(b->getTarget()->getWorldAABB()))
                {
                    b->getTarget()->getStateMachine().changeState(&EnemyDieState::getInstance());
                    b->getStateMachine().changeState(&BulletDieState::getInstance());
                }
            }

            b->update(deltaTime);
        }

        for (auto &e : Global::getInstance().enemy.enemies)
        {
            if (e->getStateMachine().getCurrentState() == &EnemyDieState::getInstance())
            {
                continue;
            }

            if (e->getWorldAABB().intersects(*playerAABB))
            {
                glfwSetWindowShouldClose(window, true);
            }

            e->getModel()->getShader()->use();
            e->getModel()->getShader()->setMat4("mvp", glm::value_ptr(projection * view * e->getModel()->getModelMatrix()));
            e->update(deltaTime);
        }

        std::string typed = Global::getInstance().player.currentTypedWord;
        float scale = 1.0f, width = 0.0f;
        const auto &chars = Global::getInstance().text->getCharacters();
        for (char c : typed)
        {
            if (chars.count(c))
                width += (chars.at(c).advance >> 6) * scale;
        }
        float x = (Global::getInstance().screenWidth - width) / 2.0f;
        float y = 50.0f;
        Global::getInstance().text->renderText(typed, x, y, scale, glm::vec3(0.2f, 0.2f, 0.2f));

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete[] vertices;
    delete[] indices;
    delete playerAABB;
    deleteTriangleMesh();

    glfwTerminate();
    return 0;
}