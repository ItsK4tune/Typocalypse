#pragma once

#include "state.h"

template <typename OwnerType>
class StateMachine {
public:
    StateMachine(OwnerType* owner) : owner(owner), currentState(nullptr) {}

    void changeState(State<OwnerType>* newState) {
        if (currentState) currentState->exit(owner);
        currentState = newState;
        if (currentState) currentState->enter(owner);
    }

    void update(float deltaTime) {
        if (currentState) currentState->update(owner, deltaTime);
    }

private:
    OwnerType* owner;
    State<OwnerType>* currentState;
};