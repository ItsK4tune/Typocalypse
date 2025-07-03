#include <cmath>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "vertex.h"

void generateCircleMesh(Vertex *&outVertices, GLuint *&outIndices, unsigned int &vertexCount, unsigned int &indexCount, int segments = 64, float radius = 1.0f);
void generateRectangleMesh(Vertex *&vertices, GLuint *&indices, unsigned int &vertexCount, unsigned int &indexCount, float width = 0.05f, float height = 0.05f);