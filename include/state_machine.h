#pragma once

#include "state.h"

template <typename OwnerType>
class StateMachine {
public:
    StateMachine(OwnerType* owner) : owner(owner), currentState(nullptr) {}

    ~StateMachine() {
        if (currentState) {
            currentState->exit(owner);
        }
	}

    State<OwnerType>* getCurrentState() const {
        return currentState;
	}

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