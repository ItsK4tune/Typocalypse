#pragma once

#include "state.h"
#include "global/global.h"

class GlobalGameOverState : public State<Global>
{
public:
    static GlobalGameOverState &getInstance();

    void enter(Global *global) override;
    void update(Global *global, float deltaTime) override;
    void exit(Global *global) override;
private:
    GlobalGameOverState();
};