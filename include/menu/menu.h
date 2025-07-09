#pragma once

#include <vector>
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include "utilities/text_renderer.h"
#include "menu/menu_state_machine.h"

struct MenuItem {
    std::string text;
    glm::vec2 position;
    float baseScale;
    glm::vec3 baseColor;

    MenuItem(const std::string& t,
             const glm::vec2& pos,
             float s = 1.0f,
             const glm::vec3& c = glm::vec3(1.0f))
        : text(t), position(pos), baseScale(s), baseColor(c) {}
};

class Menu {
public:
    Menu();
    Menu(std::shared_ptr<TextRenderer> renderer);

    void addItem(const std::string& text,
                 const glm::vec2& pos,
                 float scale = 1.0f,
                 const glm::vec3& color = glm::vec3(1.0f));

    void setItem(size_t index,
                 const glm::vec2& pos,
                 float scale,
                 const glm::vec3& color);
    void setTextRenderer(std::shared_ptr<TextRenderer> text);

    void clear();

    void moveUp();
    void moveDown();
    int getSelectedIndex() const;

    void render();

    MenuStateMachine& getStateMachine();

    void update(float deltaTime);
    void changeState(State<Menu> *newState);

private:
    std::vector<MenuItem> items;
    std::shared_ptr<TextRenderer> textRenderer;
    int selectedIndex = 0;
    MenuStateMachine stateMachine;

    const float hoverScaleBoost = 0.2f;
    const glm::vec3 selectedColor = glm::vec3(1.0f);
};
