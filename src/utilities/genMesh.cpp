#include "utilities/genMesh.h"

void generateCircleMesh(Vertex *&outVertices, GLuint *&outIndices, unsigned int &vertexCount, unsigned int &indexCount, int segments, float radius)
{
    vertexCount = segments + 2;
    indexCount = segments * 3;

    outVertices = new Vertex[vertexCount];
    outIndices = new GLuint[indexCount];

    outVertices[0] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec2(0.5f, 0.5f)};

    for (int i = 0; i <= segments; ++i)
    {
        float angle = 2.0f * glm::pi<float>() * i / segments;
        float x = cos(angle) * radius;
        float y = sin(angle) * radius;

        outVertices[i + 1] = {
            glm::vec3(x, y, 0.0f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec2((x + 1.0f) * 0.5f, (y + 1.0f) * 0.5f)};
    }

    for (int i = 0; i < segments; ++i)
    {
        outIndices[i * 3 + 0] = 0;
        outIndices[i * 3 + 1] = i + 1;
        outIndices[i * 3 + 2] = i + 2;
    }
}

void generateRectangleMesh(Vertex *&vertices, GLuint *&indices, unsigned int &vertexCount, unsigned int &indexCount, float width, float height, glm::vec3 color)
{
    vertexCount = 4;
    indexCount = 6;

    vertices = new Vertex[vertexCount];
    indices = new GLuint[indexCount]{0, 1, 2, 2, 3, 0};

    float w = width / 2.0f;
    float h = height / 2.0f;

    vertices[0] = {{-w, -h, 0.0f}, {1, 0, 0}, {0, 0, 1}, {0, 0}};
    vertices[1] = {{w, -h, 0.0f}, {0, 1, 0}, {0, 0, 1}, {1, 0}};
    vertices[2] = {{w, h, 0.0f}, {0, 0, 1}, {0, 0, 1}, {1, 1}};
    vertices[3] = {{-w, h, 0.0f}, {1, 1, 0}, {0, 0, 1}, {0, 1}};

    for (unsigned int i = 0; i < vertexCount; ++i)
    {
        vertices[i].color = color;
    }
}

void generatetriangleMesh(Vertex *&vertices, GLuint *&indices, unsigned int &vertexCount, unsigned int &indexCount, float headLength, float tailLength, glm::vec3 color)
{
    vertexCount = 3;
    indexCount = 3;

    vertices = new Vertex[vertexCount];
    indices = new GLuint[indexCount]{0, 1, 2};

    float x = tailLength / 2.0f;
    float y = headLength / 2.0f;

    vertices[0] = {{0.0f, y, 0.0f}};
    vertices[1] = {{x, -y, 0.0f}};
    vertices[2] = {{-x, -y, 0.0f}};

    for (unsigned int i = 0; i < vertexCount; ++i)
    {
        vertices[i].color = color;
    }
}
