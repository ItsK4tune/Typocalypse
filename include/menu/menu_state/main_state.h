#pragma once

#include "state.h"
#include "menu/menu.h"

class MenuMainState : public State<Menu>
{
public:
    static MenuMainState &getInstance();

    void enter(Menu *enemy) override;
    void update(Menu *enemy, float deltaTime) override;
    void exit(Menu *enemy) override;
private:
    MenuMainState();
};