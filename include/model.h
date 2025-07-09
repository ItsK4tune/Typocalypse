#pragma once

#include <memory>
#include <vector>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "vertex.h"
#include "shader.h"
#include "utilities/AABB.h"

class Model
{
public:
    Model();
    Model(std::shared_ptr<std::vector<Vertex>> vertices, std::shared_ptr<std::vector<GLuint>> indices);
    Model(const std::string &filePath);
    Model(const Model &other);
    ~Model();

    std::shared_ptr<Shader> getShader() const { return shader; }
    glm::vec3 getPosition() const { return position; }
    glm::vec3 getRotation() const { return rotation; }
    glm::vec3 getScale() const { return scale; }
    glm::mat4 getModelMatrix() const;
    AABB getAABB() const;

    void setShader(std::shared_ptr<Shader> shader);
    void setPosition(const glm::vec3 &pos) { position = pos; }
    void setRotation(const glm::vec3 &rot) { rotation = rot; }
    void setScale(const glm::vec3 &scl) { scale = scl; }

    void loadModel(const std::string &filePath);
    void loadVertexData(std::shared_ptr<std::vector<Vertex>> vertices, std::shared_ptr<std::vector<GLuint>> indices);
    void initialize();
    void cleanup();
    void draw();

private:
    unsigned int VAO, VBO, EBO;
    std::shared_ptr<std::vector<Vertex>> vertices;
    std::shared_ptr<std::vector<GLuint>> indices;
    std::shared_ptr<Shader> shader;

    glm::vec3 position{0.0f};
    glm::vec3 rotation{0.0f};
    glm::vec3 scale{1.0f};
};