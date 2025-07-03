#pragma once

#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color = {1.0f, 1.0f, 1.0f};
    glm::vec3 normal = {0.0f, 0.0f, 0.0f};
    glm::vec2 texCoords = {0.0f, 0.0f};
};
