#pragma once

#include <string>
#include <glm/glm.hpp>
#include <memory>

#include "utilities/text_renderer.h"
#include "display/display_element.h"

class DisplayTextItem : public IDisplayElement
{
public:
    DisplayTextItem(const std::string &text,
                    const glm::vec2 &pos,
                    float scale,
                    const glm::vec4 &color,
                    std::shared_ptr<TextRenderer> renderer);

    void update(float dt) override;
    void render() override;
    bool isVisible() const override;

private:
    std::string text;
    glm::vec2 position;
    float baseScale;
    glm::vec4 baseColor;
    float currentAlpha = 0.0f;
    bool fadeIn = true;
    std::shared_ptr<TextRenderer> textRenderer;
};