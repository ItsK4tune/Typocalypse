#pragma once

#include "state.h"
#include "global.h"

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