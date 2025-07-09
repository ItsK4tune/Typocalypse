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
    std::shared_ptr<Model> getModel() const;
    PlayerStateMachine &getStateMachine();
    const AABB &getLocalAABB() const;
    AABB getWorldAABB() const;

    void setLocalAABB(const AABB &box);

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