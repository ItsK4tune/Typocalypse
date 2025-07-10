#pragma once

class IMenuElement {
public:
    virtual ~IMenuElement() = default;

    virtual void update(float dt) = 0;
    virtual void render() = 0;
    virtual bool isVisible() const = 0;
};