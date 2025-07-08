#pragma once

#include "state.h"
#include "global/global.h"

class GlobalMenuState : public State<Global>
{
public:
    static GlobalMenuState &getInstance();

    void enter(Global *global) override;
    void update(Global *global, float deltaTime) override;
    void exit(Global *global) override;
private:
    GlobalMenuState();
};