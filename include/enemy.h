#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "model.h"

class Enemy
{
public:
    Enemy(std::shared_ptr<Model> m) : model(m) {}

    std::shared_ptr<Model> getModel() const { return model; }

    void updateDirection(float deltaTime, glm::vec3 playerPosition);
    void move(float deltaTime);
    void draw();

private:
    std::shared_ptr<Model> model;
    glm::vec3 direction;
    float speed = 0.1f;
};
