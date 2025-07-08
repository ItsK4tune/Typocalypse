#pragma once

#include "state.h"
#include "global/global.h"

class GlobalPlayState : public State<Global>
{
public:
    static GlobalPlayState &getInstance();

    void enter(Global *global) override;
    void update(Global *global, float deltaTime) override;
    void exit(Global *global) override;
private:
    GlobalPlayState();
};