#pragma once

#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec4 color = glm::vec4(1.0f);
    glm::vec3 normal = glm::vec3(0.0f);
    glm::vec2 texCoords = glm::vec2(0.0f);
};
