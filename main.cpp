#include <sstream>
#include <glm/gtc/type_ptr.hpp>

#include "global.h"
#include "camera.h"
#include "model.h"
#include "enemy.h"
#include "enemy_state.h"

#include "utilities/init.h"
#include "utilities/genMesh.h"
#include "utilities/text_renderer.h"

Camera *camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

int main()
{
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

    // enemy
    Vertex *enemyVertices = nullptr;
    GLuint *enemyIndices = nullptr;
    unsigned int enemyVertexCount = 0;
    unsigned int enemyIndexCount = 0;

    generatetriangleMesh(enemyVertices, enemyIndices, enemyVertexCount, enemyIndexCount, 0.12f, 0.1f, glm::vec3(1.0f, 1.0f, 0.0f));
    Model enemyModel(enemyVertices, enemyVertexCount, enemyIndices, enemyIndexCount);
    enemyModel.setShader(std::make_shared<Shader>(shader));
    enemyModel.setPosition(glm::vec3(-2.0f, -1.0f, 0.0f));

    CreepEnemy enemy(std::make_shared<Model>(enemyModel));

    double lastTime = glfwGetTime();
    float lastFrame = glfwGetTime();
    int frames = 0;

    float totalTime = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        frames++;
        if (currentFrame - lastTime >= 1.0)
        {
            std::stringstream ss;
            ss << "Typocalypse - FPS: " << frames;
            glfwSetWindowTitle(window, ss.str().c_str());
            frames = 0;
            lastTime += 1.0;
        }

        glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        // enemy logic
        static bool initialized = false;
        if (!initialized)
        {
            enemy.changeState(&EnemyIdleState::getInstance());
            initialized = true;
        }

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            if (enemy.getStateMachine().getCurrentState() != &EnemyIdleState::getInstance())
                enemy.changeState(&EnemyIdleState::getInstance());
        }
        bool wPressed = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
        bool sPressed = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;

        if (wPressed || sPressed)
        {
            glm::vec3 direction = glm::normalize(model.getPosition() - enemy.getModel()->getPosition());
            direction = wPressed ? direction : -direction;

            enemy.setDirection(direction);

            if (enemy.getStateMachine().getCurrentState() != &EnemyMoveState::getInstance())
            {
                enemy.changeState(&EnemyMoveState::getInstance());
            }
        }

        enemy.update(deltaTime);

        glm::mat4 projection = camera->getPerspectiveProjection(45.0f, (float)Global::screenWidth / (float)Global::screenHeight, 0.1f, 100.0f);
        glm::mat4 view = camera->getViewMatrix();

        // player draw
        glm::mat4 mvp = projection * view * model.getModelMatrix();
        model.getShader()->use();
        model.getShader()->setMat4("mvp", glm::value_ptr(mvp));
        model.draw();

        // enemy draw
        glm::mat4 enemyMVP = projection * view * enemy.getModel()->getModelMatrix();
        enemy.getModel()->getShader()->use();
        enemy.getModel()->getShader()->setMat4("mvp", glm::value_ptr(enemyMVP));
        enemy.draw();

        glm::vec3 enemyPos = enemy.getModel()->getPosition();
        glm::vec4 worldPos = glm::vec4(enemyPos, 1.0f);

        glm::vec4 clipSpacePos = projection * view * worldPos;
        if (clipSpacePos.w > 0.0f)
        {
            glm::vec3 ndc = glm::vec3(clipSpacePos) / clipSpacePos.w; // [-1, 1]
            float x = (ndc.x * 0.5f + 0.5f) * Global::screenWidth;
            float y = (ndc.y * 0.5f + 0.5f) * Global::screenHeight;

            // Dịch chữ xuống dưới enemy một chút (ví dụ 20px)
            y -= 20.0f;

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            text.renderText(enemy.getWord(), x, y, 0.7f, glm::vec3(0.1f, 0.1f, 0.1f));
        }

        std::string textToRender = Global::currentTypedWord;
        float scale = 1.0f;
        float textWidth = 0.0f;

        const auto &chars = text.getCharacters(); // dùng getter

        // Tính chiều rộng chuỗi để căn giữa
        for (char c : textToRender)
        {
            if (chars.count(c))
            {
                textWidth += (chars.at(c).advance >> 6) * scale;
            }
        }

        float x = (Global::screenWidth - textWidth) / 2.0f;
        float y = 50.0f; // cách mép dưới màn hình 50px
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        text.renderText(textToRender, x, y, scale, glm::vec3(0.2f, 0.2f, 0.2f));

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete[] vertices;
    delete[] indices;
    delete[] enemyVertices;
    delete[] enemyIndices;

    glfwTerminate();
    return 0;
}