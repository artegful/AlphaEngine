#include "ProjectionCamera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Alpha
{
    ProjectionCamera::ProjectionCamera(glm::vec2 size) : ProjectionCamera(size.x, size.y)
    { }

    ProjectionCamera::ProjectionCamera(float width, float height) :
        projectionMatrix(glm::ortho<float>(-width, width, -height, height)),
        aspectRatio(width / height),
        zoom(width / aspectRatio)
    { }

    ProjectionCamera::ProjectionCamera(float aspectRatio) :
        aspectRatio(aspectRatio),
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

    float ProjectionCamera::GetAspectRatio() const
    {
        return aspectRatio;
    }

    void ProjectionCamera::SetAspectRatio(float aspectRatio)
    {
        this->aspectRatio = aspectRatio;

        UpdateProjectionMatrix();
    }

    const glm::mat4& ProjectionCamera::GetProjectionMatrix() const
    {
        return projectionMatrix;
    }

    void ProjectionCamera::UpdateProjectionMatrix()
    {
        projectionMatrix = glm::ortho<float>(-zoom * aspectRatio, zoom * aspectRatio, -zoom, zoom);
    }
}

