#include "Camera.h"

Camera::Camera(const glm::vec3 &position, const glm::vec3 &front, const glm::vec3 &up)
    : position(position), front(glm::normalize(front)), up(glm::normalize(up)) {}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getPerspectiveProjection(float fov, float aspect, float near, float far) const
{
    return glm::perspective(glm::radians(fov), aspect, near, far);
}

glm::mat4 Camera::getOrthoProjection(float left, float right, float bottom, float top, float near, float far) const
{
    return glm::ortho(left, right, bottom, top, near, far);
}
