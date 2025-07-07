#pragma once

#include <memory>
#include <string>
#include <glm/glm.hpp>
#include "bullet_state_machine.h"
#include "model.h"
#include "enemy.h"

class Bullet
{
public:
    Bullet(std::shared_ptr<Model> m);
    ~Bullet();

    void setDirection(const glm::vec3 &dir);
    void setTarget(std::shared_ptr<EnemyAbstract> e) { target = e; }
    void setVelocity(const glm::vec3 &v) { velocity = v; }
    void setAcceleration(const glm::vec3 &a) { acceleration = a; }
    void setMaxSpeed(float s) { maxSpeed = s; }

    BulletStateMachine &getStateMachine() { return stateMachine; }
    std::shared_ptr<Model> getModel() const { return model; }
    std::shared_ptr<EnemyAbstract> getTarget() const { return target; }

    void update(float deltaTime);
    void changeState(State<Bullet> *newState);
    void draw();
    void move();

private:
    std::shared_ptr<Model> model;
    glm::vec3 direction;
    glm::vec3 velocity = glm::vec3(0.0f);
    glm::vec3 acceleration = glm::vec3(0.0f);
    float maxSpeed = 0.5f;
    float accelerationRate = 3.0f;

    BulletStateMachine stateMachine;

    std::shared_ptr<EnemyAbstract> target;
};