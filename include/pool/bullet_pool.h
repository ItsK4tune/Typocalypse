#pragma once

#include <vector>
#include <memory>

#include "shader.h"
#include "bullet/bullet.h"
#include "utilities/AABB.h"

class BulletPool
{
public:
    std::vector<std::shared_ptr<Bullet>> bullets;

    void init(size_t count, const Shader &shader);
    Bullet *spawn(const glm::vec3 &pos, const std::shared_ptr<EnemyAbstract> &target);
    void clear();

private:
    std::shared_ptr<std::vector<Vertex>> bulletVertices;
    std::shared_ptr<std::vector<GLuint>> bulletIndices;

    AABB initRectangleMesh();
};