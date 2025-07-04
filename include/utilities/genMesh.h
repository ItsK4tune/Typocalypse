#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glad/glad.h>
#include "vertex.h"

void generateCircleMesh(Vertex *&outVertices, GLuint *&outIndices, unsigned int &vertexCount, unsigned int &indexCount, int segments = 64, float radius = 0.2f);
void generateRectangleMesh(Vertex *&vertices, GLuint *&indices, unsigned int &vertexCount, unsigned int &indexCount, float width = 0.05f, float height = 0.05f);
void generatetriangleMesh(Vertex*& vertices, GLuint*& indices, unsigned int& vertexCount, unsigned int& indexCount, float headLength = 0.01f, float tailLength = 0.01f, glm::vec3 color = glm::vec3(1.0f));