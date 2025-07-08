#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "utilities/AABB.h"

#include "player_state_machine.h"
#include "player_state.h"
#include "model.h"
#include "state.h"

class Player
{
public:
    Player(std::shared_ptr<Model> m);
    ~Player();

    // Getters
    std::shared_ptr<Model> getModel() const { return model; }
    PlayerStateMachine &getStateMachine() { return stateMachine; }
    const AABB &getLocalAABB() const { return localAABB; }
    AABB getWorldAABB() const
    {
        glm::mat4 modelMat = model->getModelMatrix();
        glm::vec3 corners[8] = {
            localAABB.min,
            glm::vec3(localAABB.min.x, localAABB.min.y, localAABB.max.z),
            glm::vec3(localAABB.min.x, localAABB.max.y, localAABB.min.z),
            glm::vec3(localAABB.min.x, localAABB.max.y, localAABB.max.z),
            glm::vec3(localAABB.max.x, localAABB.min.y, localAABB.min.z),
            glm::vec3(localAABB.max.x, localAABB.min.y, localAABB.max.z),
            glm::vec3(localAABB.max.x, localAABB.max.y, localAABB.min.z),
            localAABB.max};

        glm::vec3 minPt(FLT_MAX), maxPt(-FLT_MAX);
        for (int i = 0; i < 8; ++i)
        {
            glm::vec3 transformed = glm::vec3(modelMat * glm::vec4(corners[i], 1.0f));
            minPt = glm::min(minPt, transformed);
            maxPt = glm::max(maxPt, transformed);
        }

        return AABB(minPt, maxPt);
    }

    // Setter
    void setLocalAABB(const AABB &box) { localAABB = box; }

    // Update player state
    void
    update(float deltaTime);
    void changeState(State<Player> *newState);

    void draw();

private:
    PlayerStateMachine stateMachine;
    std::shared_ptr<Model> model;
    AABB localAABB;
};