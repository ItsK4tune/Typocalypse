#pragma once

#include <memory>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "vertex.h"
#include "shader.h"

class Model
{
public:
    Model();
    Model(Vertex *vertices, unsigned int vertexCount, GLuint *indices, unsigned int indexCount);
    Model(const char *path);
    ~Model();

    std::shared_ptr<Shader> getShader() const { return shader; }
    glm::vec3 getPosition() const { return position; }
    glm::vec3 getRotation() const { return rotation; }
    glm::vec3 getScale() const { return scale; }

    void setShader(std::shared_ptr<Shader> shader);
    void setPosition(const glm::vec3 &pos) { position = pos; }
    void setRotation(const glm::vec3 &rot) { rotation = rot; }
    void setScale(const glm::vec3 &scl) { scale = scl; }

    void loadModel(const char *path);
    void loadVertexData(Vertex *vertices, unsigned int vertexCount, GLuint *indices, unsigned int indexCount);
    void initialize();
    void cleanup();
    void draw();
    glm::mat4 getModelMatrix() const;

private:
    unsigned int VAO, VBO, EBO;
    Vertex *vertices;
    GLuint *indices;
    unsigned int vertexCount;
    unsigned int indexCount;
    std::shared_ptr<Shader> shader;

    glm::vec3 position{0.0f};
    glm::vec3 rotation{0.0f};
    glm::vec3 scale{1.0f};
};