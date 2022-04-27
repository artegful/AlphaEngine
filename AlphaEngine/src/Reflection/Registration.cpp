#include "rttr/registration.h"

#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/CameraComponent.h"

#include "MetadataType.h"
#include "MetadataVectorUsage.h"

RTTR_REGISTRATION
{
	using namespace rttr;

	registration::class_<Alpha::TransformComponent>("TransformComponent")
		(
			metadata(Alpha::MetadataType::ComponentNecessity, true)
		)
		.property("Transform", &Alpha::TransformComponent::Transform)
		(
			policy::prop::bind_as_ptr
		);

	registration::class_<Alpha::SpriteComponent>("SpriteComponent")
		.property("Color", &Alpha::SpriteComponent::Color)
		(
			metadata(Alpha::MetadataType::VectorUsage, Alpha::MetadataVectorUsage::Color)
		);

	registration::class_<Alpha::Transform>("Transform")
		.property("Position", &Alpha::Transform::Position)
		.property("Rotation", &Alpha::Transform::Rotation)
		.property("Scale", &Alpha::Transform::Scale);

	registration::class_<Alpha::CameraComponent>("CameraComponent")
		.property("Camera", &Alpha::CameraComponent::Camera)
		(
			policy::prop::bind_as_ptr
		);

	registration::class_<Alpha::ProjectionCamera>("ProjectionCamera")
		.property("Size", &Alpha::ProjectionCamera::GetSize, &Alpha::ProjectionCamera::SetSize)
		.property("Zoom", &Alpha::ProjectionCamera::GetZoom, &Alpha::ProjectionCamera::SetZoom);
}

