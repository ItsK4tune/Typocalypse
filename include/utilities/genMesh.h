#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glad/glad.h>
#include "vertex.h"

void generateCircleMesh(Vertex *&outVertices, GLuint *&outIndices, unsigned int &vertexCount, unsigned int &indexCount, int segments, float radius);
void generateRectangleMesh(Vertex *&vertices, GLuint *&indices, unsigned int &vertexCount, unsigned int &indexCount, float width, float height, glm::vec3 color);
void generatetriangleMesh(Vertex *&vertices, GLuint *&indices, unsigned int &vertexCount, unsigned int &indexCount, float headLength, float tailLength, glm::vec3 color);