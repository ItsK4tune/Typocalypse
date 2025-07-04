#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "model.h"
#include "enemy_state_machine.h"

class Enemy
{
public:
    Enemy(std::shared_ptr<Model> m);

    std::shared_ptr<Model> getModel() const { return model; }
	EnemyStateMachine& getStateMachine() { return stateMachine; }

	void setDirection(const glm::vec3& dir) { direction = dir; }

	// State machine
    void update(float deltaTime);
    void changeState(State<Enemy>* newState);

	// Movement methods
	void updateModelRotation();
    void move(float deltaTime);
    void draw();

private:
	EnemyStateMachine stateMachine;
    std::shared_ptr<Model> model;
    glm::vec3 direction;
    float speed;
};
