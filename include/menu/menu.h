#pragma once

#include <vector>
#include <string>
#include <memory>
#include <glm/glm.hpp>

#include "utilities/text_renderer.h"
#include "menu/menu_state_machine.h"
#include "model.h"

struct MenuItem
{
    std::string text;
    glm::vec2 position;
    float baseScale;
    glm::vec3 baseColor;

    MenuItem(const std::string &t,
             const glm::vec2 &pos,
             float s = 1.0f,
             const glm::vec3 &c = glm::vec3(1.0f))
        : text(t), position(pos), baseScale(s), baseColor(c) {}
};

class Menu
{
public:
    Menu();
    Menu(std::shared_ptr<TextRenderer> renderer);

    void addTextItem(const std::string &text,
                     const glm::vec2 &pos,
                     float scale = 1.0f,
                     const glm::vec3 &color = glm::vec3(1.0f));
    void setTextItem(size_t index,
                     const glm::vec2 &pos,
                     float scale,
                     const glm::vec3 &color);
    void clearTexts();

    void addModel(std::shared_ptr<Model> model);
    void clearModels();

    void setTextRenderer(std::shared_ptr<TextRenderer> text);

    void moveUp();
    void moveDown();
    int getSelectedIndex() const;

    void render();
    void update(float dt);
    void changeState(State<Menu> *newState);
    MenuStateMachine &getStateMachine();

private:
    std::vector<MenuItem> textItems;
    std::vector<std::shared_ptr<Model>> uiModels;

    std::shared_ptr<TextRenderer> textRenderer;
    MenuStateMachine stateMachine;

    int selectedIndex = 0;
    const float hoverScaleBoost = 0.2f;
    const glm::vec3 selectedColor = glm::vec3(1.0f);
};
