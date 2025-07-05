#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <ctime>

#include "global.h"
#include "camera.h"
#include "model.h"
#include "enemy.h"
#include "enemy_state.h"

#include "utilities/init.h"
#include "utilities/genMesh.h"
#include "utilities/text_renderer.h"
#include "utilities/spawn_enemy.h"

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    GLFWwindow *window = createWindow(Global::screenWidth, Global::screenHeight, "Typocalypse");

    // text renderer
    TextRenderer text(Global::screenWidth, Global::screenHeight);
    text.load("../resources/fonts/TimesRegular.ttf", 48);

    // player
    Vertex *vertices = nullptr;
    GLuint *indices = nullptr;
    unsigned int vertexCount = 0;
    unsigned int indexCount = 0;

    generateCircleMesh(vertices, indices, vertexCount, indexCount, 64, 0.05f);
    Model model(vertices, vertexCount, indices, indexCount);
    Shader shader("basic.vert", "basic.frag");
    model.setShader(std::make_shared<Shader>(shader));

    std::vector<std::string> wordList = {"cat", "dog", "fish", "bird", "mouse", "elephant", "giraffe", "lion", "tiger", "bear",
                                         "zebra", "monkey", "kangaroo", "panda", "rabbit", "fox", "wolf", "deer", "cow", "sheep"};
    initEnemyPool(wordList, shader);
    spawnInitialEnemies(Global::numberOfEnemies, model.getPosition());

    double lastTime = glfwGetTime();
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

        // Set matrices
        glm::mat4 projection = Global::camera->getPerspectiveProjection(45.0f, (float)Global::screenWidth / Global::screenHeight, 0.1f, 100.0f);
        glm::mat4 view = Global::camera->getViewMatrix();

        // Draw player
        glm::mat4 mvp = projection * view * model.getModelMatrix();
        model.getShader()->use();
        model.getShader()->setMat4("mvp", glm::value_ptr(mvp));
        model.draw();

        for (auto &e : Global::enemies)
        {
            e->getModel()->getShader()->use();
            e->getModel()->getShader()->setMat4("mvp", glm::value_ptr(projection * view * e->getModel()->getModelMatrix()));
            e->update(deltaTime);

            // Text render
            if (e->getStateMachine().getCurrentState() == &EnemyDieState::getInstance())
            {
                continue; // Skip rendering if the enemy is dead
            }

            glm::vec3 pos = e->getModel()->getPosition();
            glm::vec4 clipSpace = projection * view * glm::vec4(pos, 1.0f);
            if (clipSpace.w > 0.0f)
            {
                glm::vec3 ndc = glm::vec3(clipSpace) / clipSpace.w;

                std::string word = e->getWord();
                float scale = 0.7f;
                float wordWidth = 0.0f;
                const auto &chars = text.getCharacters();
                for (char c : word)
                {
                    if (chars.count(c))
                        wordWidth += (chars.at(c).advance >> 6) * scale;
                }

                float x = (ndc.x * 0.5f + 0.5f) * Global::screenWidth - wordWidth / 2.0f;
                float y = (ndc.y * 0.5f + 0.5f) * Global::screenHeight - 50.0f;

                text.renderText(word, x, y, scale, glm::vec3(0.1f, 0.1f, 0.1f));
            }
        }

        // Render typed word ở dưới cùng
        std::string typed = Global::currentTypedWord;
        float scale = 1.0f, width = 0.0f;
        const auto &chars = text.getCharacters();
        for (char c : typed)
        {
            if (chars.count(c))
                width += (chars.at(c).advance >> 6) * scale;
        }
        float x = (Global::screenWidth - width) / 2.0f;
        float y = 50.0f;
        text.renderText(typed, x, y, scale, glm::vec3(0.2f, 0.2f, 0.2f));

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete[] vertices;
    delete[] indices;

    glfwTerminate();
    return 0;
}