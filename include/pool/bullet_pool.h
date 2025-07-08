#pragma once

#include <vector>
#include <memory>

#include "shader.h"
#include "bullet/bullet.h"
#include "utilities/AABB.h"

class BulletPool
{
public:
    ~BulletPool();
    std::vector<std::shared_ptr<Bullet>> bullets;

    void init(size_t count, const Shader &shader);
    Bullet *spawn(const glm::vec3 &pos, const std::shared_ptr<EnemyAbstract> &target);

private:
    Vertex *bulletVertices = nullptr;
    GLuint *bulletIndices = nullptr;
    unsigned int bulletVertexCount = 0;
    unsigned int bulletIndexCount = 0;

    AABB initRectangleMesh();
};