#pragma once

#include "state.h"
#include "player.h"

class PlayerIdleState : public State<Player>
{
public: 
    static PlayerIdleState &getInstance();

    void enter(Player *enemy) override;
    void update(Player *enemy, float deltaTime) override;
    void exit(Player *enemy) override;

private:
    PlayerIdleState();
};