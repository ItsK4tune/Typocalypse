#pragma once

#include <vector>
#include <string>
#include <memory>
#include <glm/glm.hpp>

#include "utilities/text_renderer.h"
#include "display/display_state_machine.h"
#include "model.h"

struct DisplayItem
{
    std::string text;
    glm::vec2 position;
    float baseScale;
    glm::vec4 baseColor;

    DisplayItem(const std::string &t,
                const glm::vec2 &pos,
                float s = 1.0f,
                const glm::vec4 &c = glm::vec4(1.0f))
        : text(t), position(pos), baseScale(s), baseColor(c) {}
};

class Display
{
public:
    Display();
    Display(std::shared_ptr<TextRenderer> renderer);

    void addTextItem(const std::string &text,
                     const glm::vec2 &pos,
                     float scale = 1.0f,
                     const glm::vec4 &color = glm::vec4(1.0f));
    void setTextItem(size_t index,
                     const glm::vec2 &pos,
                     float scale,
                     const glm::vec4 &color);
    void clearTexts();

    void addModel(std::shared_ptr<Model> model);
    void clearModels();

    void setTextRenderer(std::shared_ptr<TextRenderer> text);

    void moveUp();
    void moveDown();
    int getSelectedIndex() const;

    void render();
    void update(float dt);
    void changeState(State<Display> *newState);
    DisplayStateMachine &getStateMachine();

private:
    std::vector<DisplayItem> textItems;
    std::vector<std::shared_ptr<Model>> uiModels;

    std::shared_ptr<TextRenderer> textRenderer;
    DisplayStateMachine stateMachine;

    int selectedIndex = 0;
    const float hoverScaleBoost = 0.2f;
    const glm::vec4 selectedColor = glm::vec4(1.0f);
};
