#include "PerspectiveCamera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Alpha
{
    PerspectiveCamera::PerspectiveCamera(float width, float height, float fov) :
        zoom(1.0f),
        aspectRatio(width / height),
        fov(fov),
        nearFarPlane(0.0f, 300.0f)
    {
        UpdateProjectionMatrix();
    }

    PerspectiveCamera::PerspectiveCamera(float aspectRatio, float fov) :
        zoom(1.0f),
        aspectRatio(aspectRatio),
        fov(fov),
        nearFarPlane(0.1f, 300.0f)
    {
        UpdateProjectionMatrix();
    }

    float PerspectiveCamera::GetZoom() const
    {
        return zoom;
    }

    void PerspectiveCamera::SetZoom(float zoom)
    {
        this->zoom = zoom < MIN_ZOOM ? MIN_ZOOM : zoom > MAX_ZOOM ? MAX_ZOOM : zoom;
        UpdateProjectionMatrix();
    }

    float PerspectiveCamera::GetAspectRatio() const
    {
        return aspectRatio;
    }

    void PerspectiveCamera::SetAspectRatio(float aspectRatio)
    {
        this->aspectRatio = aspectRatio;
        UpdateProjectionMatrix();
    }

    glm::vec2 PerspectiveCamera::GetNearFarPlane() const
    {
        return nearFarPlane;
    }

    void PerspectiveCamera::SetNearFarPlane(glm::vec2 nearFarPlane)
    {
        this->nearFarPlane = nearFarPlane;
        UpdateProjectionMatrix();
    }

    const glm::mat4& PerspectiveCamera::GetProjectionMatrix() const
    {
        return projectionMatrix;
    }

    void PerspectiveCamera::UpdateProjectionMatrix()
    {
        projectionMatrix = glm::perspective<float>(glm::radians(fov * zoom), aspectRatio, nearFarPlane.x, nearFarPlane.y);
    }
}

