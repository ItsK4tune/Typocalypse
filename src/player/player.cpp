#include "player/player.h"

Player::Player(std::shared_ptr<Model> m)
    : model(m), stateMachine(this)
{
    model->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
}

Player::~Player()
{
    if (model)
    {
        model->cleanup();
    }
}

void Player::changeState(State<Player> *newState)
{
    stateMachine.changeState(newState);
}

void Player::update(float deltaTime)
{
    stateMachine.update(deltaTime);
}

void Player::draw()
{
    model->draw();
}