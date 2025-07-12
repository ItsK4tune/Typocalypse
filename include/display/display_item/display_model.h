#pragma once

#include <string>
#include <memory>

#include "display/display_element.h"
#include "utilities/text_renderer.h"
#include "global/global.h"
#include "model.h"

class DisplayModelItem : public IDisplayElement
{
public:
    DisplayModelItem(std::shared_ptr<Model> model)
        : model(model), currentAlpha(0.0f), fadeIn(true) {}

    void update(float dt) override
    {
        float speed = 1.5f;
        currentAlpha += (fadeIn ? dt : -dt) * speed;
        currentAlpha = glm::clamp(currentAlpha, 0.0f, 1.0f);
    }

    void render() override
    {
        if (!model || currentAlpha <= 0.0f)
            return;

        model->getShader()->use();

        glm::mat4 projection = Global::getInstance().camera->getOrthoProjection(
            0.0f, Global::getInstance().screenWidth,
            0.0f, Global::getInstance().screenHeight,
            -1.0f, 1.0f);
        glm::mat4 mvp = projection * model->getModelMatrix();
        model->getShader()->setMat4("mvp", glm::value_ptr(mvp));

        model->draw();
    }

    void setFadeIn(bool enable) { fadeIn = enable; }
    bool isVisible() const override { return currentAlpha > 0.0f; }

private:
    std::shared_ptr<Model> model;
    float currentAlpha;
    bool fadeIn;
};
