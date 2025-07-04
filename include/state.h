#pragma once

template <typename OwnerType>
class State {
public:
    virtual void enter(OwnerType* owner) = 0;
    virtual void update(OwnerType* owner, float deltaTime) = 0;
    virtual void exit(OwnerType* owner) = 0;
    virtual ~State() = default;
};