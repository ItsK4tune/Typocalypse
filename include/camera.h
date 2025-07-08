#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

class Camera
{
public:
    Camera(const glm::vec3 &position, const glm::vec3 &front, const glm::vec3 &up);

    glm::vec3 getPosition() const { return position; }
    glm::vec3 getFront() const { return front; }
    glm::vec3 getUp() const { return up; }

    void setPosition(const glm::vec3 &pos) { position = pos; }
    void setFront(const glm::vec3 &f) { front = glm::normalize(f); }
    void setUp(const glm::vec3 &u) { up = glm::normalize(u); }

    glm::mat4 getViewMatrix() const;
    glm::mat4 getPerspectiveProjection(float fov, float aspect, float near, float far) const;
    glm::mat4 getOrthoProjection(float left, float right, float bottom, float top, float near, float far) const;

private:
    glm::vec3 position;
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
};

using CameraPtr = std::shared_ptr<Camera>;
