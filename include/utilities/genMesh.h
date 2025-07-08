#include <memory>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "vertex.h"

void generateCircleMesh(std::shared_ptr<std::vector<Vertex>> &vertices, std::shared_ptr<std::vector<GLuint>> &indices, int segments, float radius, glm::vec3 color);
void generateRectangleMesh(std::shared_ptr<std::vector<Vertex>> &vertices, std::shared_ptr<std::vector<GLuint>> &indices, float width, float height, glm::vec3 color);
void generatetriangleMesh(std::shared_ptr<std::vector<Vertex>> &vertices, std::shared_ptr<std::vector<GLuint>> &indices, float headLength, float tailLength, glm::vec3 color);