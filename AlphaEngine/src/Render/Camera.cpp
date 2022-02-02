#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Alpha
{
    Camera::Camera(glm::vec2 size) : Camera(size.x, size.y)
    { }

    Camera::Camera(float width, float height) :
        projectionMatrix(glm::ortho<float>(-width, width, -height, height))
    { }

    Transform& Camera::GetTransform()
    {
        return transform;
    }

    glm::mat4 Camera::GetProjectionMatrix() const
    {
        return projectionMatrix;
    }

    glm::mat4 Camera::GetViewMatrix() const
    {
        return glm::inverse(transform.GetTransformMatrix());
    }

    glm::mat4 Camera::GetViewProjectionMatrix() const
    {
        return projectionMatrix * GetViewMatrix();
    }


}

