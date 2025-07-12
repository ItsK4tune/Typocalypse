#pragma once

class IDisplayElement
{
public:
    virtual ~IDisplayElement() = default;

    virtual void update(float dt) = 0;
    virtual void render() = 0;
    virtual bool isVisible() const = 0;
};