#include <iostream>

#include "global/player_data.h"
#include "utilities/genMesh.h"

void PlayerData::init(const Shader &shader){
    AABB localAABB = initCircleMesh();

    auto playerModel = std::make_shared<Model>(playerVertices, playerIndices);
    playerModel->setShader(std::make_shared<Shader>(shader));
    player = std::make_shared<Player>(playerModel);
    player->setLocalAABB(localAABB);
}

void PlayerData::clear() {
    playerVertices.reset();
    playerIndices.reset();
}

AABB PlayerData::initCircleMesh(){
    generateCircleMesh(playerVertices, playerIndices, 64, 0.05f, glm::vec3(1.0f, 0.0f, 0.0f));

    if (!playerVertices || playerVertices->empty())
    {
        std::cerr << "[BulletPool::initRectangleMesh] bulletVertices is empty!\n";
        return AABB();
    }

    glm::vec3 min = playerVertices->at(0).position;
    glm::vec3 max = min;

    for (size_t i = 1; i < playerVertices->size(); ++i)
    {
        const glm::vec3 &pos = playerVertices->at(i).position;
        min = glm::min(min, pos);
        max = glm::max(max, pos);
    }

    return AABB(min, max);
}