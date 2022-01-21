#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Alpha
{
    Camera::Camera(int width, int height) :
        position(0),
        viewMatrix(1),
        projectionMatrix(glm::ortho<float>(-width / 10.0f, width / 10.0f, -height / 10.0f, height / 10.0f))
    { }

    glm::vec2 Camera::GetPosition()
    {
        return position;
    }

    void Camera::SetPosition(glm::vec2 position)
    {
        this->position = position;

        UpdateViewMatrix();
    }

    glm::mat4 Camera::GetProjectionMatrix()
    {
        return projectionMatrix;
    }

    glm::mat4 Camera::GetViewMatrix()
    {
        return viewMatrix;
    }

    void Camera::UpdateViewMatrix()
    {
        // to get view matrix we can use lookat
        // or reverse matrix of all transforms
        // applied to camera
        // but in 2D we do not rotate or scale camera
        // so just use inverse of translate matrix

        viewMatrix[3][0] = -position.x;
        viewMatrix[3][1] = -position.y;
    }
}

