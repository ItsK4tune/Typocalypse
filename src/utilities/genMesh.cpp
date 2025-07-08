#include "utilities/genMesh.h"
#include "glm/gtc/constants.hpp"

void generateCircleMesh(
    std::shared_ptr<std::vector<Vertex>> &vertices,
    std::shared_ptr<std::vector<GLuint>> &indices,
    int segments,
    float radius,
    glm::vec3 color)
{
    if (!vertices)
        vertices = std::make_shared<std::vector<Vertex>>();
    if (!indices)
        indices = std::make_shared<std::vector<GLuint>>();

    vertices->clear();
    indices->clear();

    vertices->push_back({
        glm::vec3(0.0f, 0.0f, 0.0f),
        color,
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec2(0.5f, 0.5f)
    });

    for (int i = 0; i <= segments; ++i)
    {
        float angle = 2.0f * glm::pi<float>() * i / segments;
        float x = cos(angle) * radius;
        float y = sin(angle) * radius;

        vertices->push_back({
            glm::vec3(x, y, 0.0f),
            color,
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec2((x + 1.0f) * 0.5f, (y + 1.0f) * 0.5f)
        });
    }

    for (int i = 0; i < segments; ++i)
    {
        indices->push_back(0);
        indices->push_back(i + 1);
        indices->push_back(i + 2);
    }
}

void generateRectangleMesh(
    std::shared_ptr<std::vector<Vertex>> &vertices,
    std::shared_ptr<std::vector<GLuint>> &indices,
    float width,
    float height,
    glm::vec3 color)
{
    unsigned int vertexCount = 4;

    vertices = std::make_shared<std::vector<Vertex>>(vertexCount);
    indices = std::make_shared<std::vector<GLuint>>(std::initializer_list<GLuint>{0, 1, 2, 2, 3, 0});

    float w = width / 2.0f;
    float h = height / 2.0f;

    (*vertices)[0] = {{-w, -h, 0.0f}, color, {0, 0, 1}, {0, 0}};
    (*vertices)[1] = {{w, -h, 0.0f}, color, {0, 0, 1}, {1, 0}};
    (*vertices)[2] = {{w, h, 0.0f}, color, {0, 0, 1}, {1, 1}};
    (*vertices)[3] = {{-w, h, 0.0f}, color, {0, 0, 1}, {0, 1}};
}

void generatetriangleMesh(
    std::shared_ptr<std::vector<Vertex>> &vertices,
    std::shared_ptr<std::vector<GLuint>> &indices, float headLength,
    float tailLength,
    glm::vec3 color)
{
    unsigned int vertexCount = 3;

    vertices = std::make_shared<std::vector<Vertex>>(vertexCount);
    indices = std::make_shared<std::vector<GLuint>>(std::initializer_list<GLuint>{0, 1, 2});

    float x = tailLength / 2.0f;
    float y = headLength / 2.0f;

    (*vertices)[0] = {{0.0f, y, 0.0f}, color};
    (*vertices)[1] = {{x, -y, 0.0f}, color};
    (*vertices)[2] = {{-x, -y, 0.0f}, color};
}
