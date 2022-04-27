#include "ProjectionCamera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Alpha
{
    ProjectionCamera::ProjectionCamera(glm::vec2 size) : ProjectionCamera(size.x, size.y)
    { }

    ProjectionCamera::ProjectionCamera(float width, float height) :
        projectionMatrix(glm::ortho<float>(-width, width, -height, height)),
        size(width, height),
        zoom(1.0f)
    { }

    ProjectionCamera::ProjectionCamera(float aspectRatio) :
        size(aspectRatio, 1.0f),
        zoom(1.0f)
    {
        UpdateProjectionMatrix();
    }

    float ProjectionCamera::GetZoom() const
    {
        return zoom;
    }

    void ProjectionCamera::SetZoom(float zoom)
    {
        this->zoom = zoom < MIN_ZOOM ? MIN_ZOOM : zoom;
        UpdateProjectionMatrix();
    }

    glm::vec2 ProjectionCamera::GetSize() const
    {
        return size;
    }

    void ProjectionCamera::SetSize(glm::vec2 size)
    {
        this->size = size;

        UpdateProjectionMatrix();
    }

    void ProjectionCamera::SetAspectRatio(float aspectRatio)
    {
        size.x = size.y * aspectRatio;

        UpdateProjectionMatrix();
    }

    const glm::mat4& ProjectionCamera::GetProjectionMatrix() const
    {
        return projectionMatrix;
    }

    void ProjectionCamera::UpdateProjectionMatrix()
    {
        projectionMatrix = glm::ortho<float>(-zoom * size.x / 2.0f, zoom * size.x / 2.0f, -zoom * size.y / 2.0f, zoom * size.y / 2.0f);
    }
}

