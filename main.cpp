#include <sstream>
#include <glm/gtc/type_ptr.hpp>

#include "global.h"
#include "model.h"
#include "enemy.h"

#include "utilities/init.h"
#include "utilities/genMesh.h"

int main()
{
    GLFWwindow *window = createWindow(Global::screenWidth, Global::screenHeight, "Typocalypse");

    // player
    Vertex *vertices = nullptr;
    GLuint *indices = nullptr;
    unsigned int vertexCount = 0;
    unsigned int indexCount = 0;

    generateCircleMesh(vertices, indices, vertexCount, indexCount, 64, 0.01f);
    Model model(vertices, vertexCount, indices, indexCount);
    Shader shader("basic.vert", "basic.frag");
    model.setShader(std::make_shared<Shader>(shader));

    // enemy
    Vertex *enemyVertices = nullptr;
    GLuint *enemyIndices = nullptr;
    unsigned int enemyVertexCount = 0;
    unsigned int enemyIndexCount = 0;

    generateRectangleMesh(enemyVertices, enemyIndices, enemyVertexCount, enemyIndexCount);
    Model enemyModel(enemyVertices, enemyVertexCount, enemyIndices, enemyIndexCount);
    enemyModel.setShader(std::make_shared<Shader>(shader));
    enemyModel.setPosition(glm::vec3(-2.0f, -1.0f, 0.0f)); // top-left corner of screen

    Enemy enemy(std::make_shared<Model>(enemyModel));

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

        glm::mat4 view = glm::lookAt(
            glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                                (float)Global::screenWidth / (float)Global::screenHeight,
                                                0.1f, 100.0f);

        // enemy logic
        enemy.updateDirection(deltaTime, model.getPosition());
        enemy.move(deltaTime);

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