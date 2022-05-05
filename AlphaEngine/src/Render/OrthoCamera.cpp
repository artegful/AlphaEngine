#include "OrthoCamera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Alpha
{
    OrthoCamera::OrthoCamera(glm::vec2 size) : OrthoCamera(size.x, size.y)
    { }

    OrthoCamera::OrthoCamera(float width, float height) :
        projectionMatrix(glm::ortho<float>(-width, width, -height, height)),
        size(width, height),
        zoom(1.0f)
    { }

    OrthoCamera::OrthoCamera(float aspectRatio) :
        size(aspectRatio, 1.0f),
        zoom(1.0f)
    {
        UpdateProjectionMatrix();
    }

    float OrthoCamera::GetZoom() const
    {
        return zoom;
    }

    void OrthoCamera::SetZoom(float zoom)
    {
        this->zoom = zoom < MIN_ZOOM ? MIN_ZOOM : zoom;
        UpdateProjectionMatrix();
    }

    glm::vec2 OrthoCamera::GetSize() const
    {
        return size;
    }

    void OrthoCamera::SetSize(glm::vec2 size)
    {
        this->size = size;

        UpdateProjectionMatrix();
    }

    void OrthoCamera::SetAspectRatio(float aspectRatio)
    {
        size.x = size.y * aspectRatio;

        UpdateProjectionMatrix();
    }

    const glm::mat4& OrthoCamera::GetProjectionMatrix() const
    {
        return projectionMatrix;
    }

    void OrthoCamera::UpdateProjectionMatrix()
    {
        projectionMatrix = glm::ortho<float>(-zoom * size.x / 2.0f, zoom * size.x / 2.0f, -zoom * size.y / 2.0f, zoom * size.y / 2.0f);
    }
}

