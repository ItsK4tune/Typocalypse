#pragma once

#include "state.h"
#include "player/player.h"

class PlayerDieState : public State<Player>
{
public:
    static PlayerDieState &getInstance();

    void enter(Player *enemy) override;
    void update(Player *enemy, float deltaTime) override;
    void exit(Player *enemy) override;

private:
    PlayerDieState();
};