#pragma once

#include "state.h"
#include "display/display.h"

class DisplayMainState : public State<Display>
{
public:
    static DisplayMainState &getInstance();

    void enter(Display *enemy) override;
    void update(Display *enemy, float deltaTime) override;
    void exit(Display *enemy) override;

private:
    DisplayMainState();
};