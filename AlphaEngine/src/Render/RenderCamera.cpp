#include "RenderCamera.h"

namespace Alpha
{
	RenderCamera::RenderCamera(const ProjectionCamera& camera, const Transform& transform) :
		camera(camera), transform(transform)
	{ }

	glm::mat4 RenderCamera::GetViewProjectionMatrix() const
	{
		return camera.GetProjectionMatrix() *  glm::inverse(transform.GetTransformMatrix());
	}

	glm::mat4 RenderCamera::GetViewProjectionMatrixWithoutTranslate() const
	{
		return camera.GetProjectionMatrix() * glm::inverse(transform.GetTransformMatrixWithoutTranslation());
	}

	const Transform& RenderCamera::GetTransform() const
	{
		return transform;
	}
}