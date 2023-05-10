#pragma once

#include "rttr/registration.h"

#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/OrthoCameraComponent.h"
#include "Components/Rigidbody2DComponent.h"
#include "Components/Box2DColliderComponent.h"

#include "MetadataType.h"
#include "MetadataVectorUsage.h"
#include "MetadataFileType.h"
#include <Components/ModelComponent.h>
#include <Components/PointLightComponent.h>

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
		)
		.property("SpritePath", &Alpha::SpriteComponent::GetPath, &Alpha::SpriteComponent::SetPath)
		(
			metadata(Alpha::MetadataType::FileType, Alpha::MetadataFileType::Sprite)
		);

	registration::class_<Alpha::Transform>("Transform")
		.constructor<>()
		.property("Position", &Alpha::Transform::Position)
		.property("Rotation", &Alpha::Transform::Rotation)
		.property("Scale", &Alpha::Transform::Scale);

	registration::class_<Alpha::OrthoCameraComponent>("OrthoCameraComponent")
		.property("Camera", &Alpha::OrthoCameraComponent::Camera)
		(
			policy::prop::bind_as_ptr
		);

	registration::class_<Alpha::OrthoCamera>("OrthoCamera")
		.property("Size", &Alpha::OrthoCamera::GetSize, &Alpha::OrthoCamera::SetSize)
		.property("Zoom", &Alpha::OrthoCamera::GetZoom, &Alpha::OrthoCamera::SetZoom);

	registration::enumeration<Alpha::Rigidbody2DComponent::BodyType>("PhysicsBodyType")
		(
			value("Static", Alpha::Rigidbody2DComponent::BodyType::Static),
			value("Dynamic", Alpha::Rigidbody2DComponent::BodyType::Dynamic),
			value("Kinematic", Alpha::Rigidbody2DComponent::BodyType::Kinematic)
		);

	registration::class_<Alpha::Rigidbody2DComponent>("Rigidbody2DComponent")
		.property("Is Fixed Rotation", &Alpha::Rigidbody2DComponent::IsFixedRotation)
		.property("Body Type", &Alpha::Rigidbody2DComponent::Type);

	registration::class_<Alpha::Box2DColliderComponent>("Box2DColliderComponent")
		.property("Offset", &Alpha::Box2DColliderComponent::Offset)
		.property("Size", &Alpha::Box2DColliderComponent::Size)
		.property("Density", &Alpha::Box2DColliderComponent::Density)
		.property("Friction", &Alpha::Box2DColliderComponent::Friction)
		.property("Restitution", &Alpha::Box2DColliderComponent::Restitution)
		.property("RestitutionThreshold", &Alpha::Box2DColliderComponent::RestitutionThreshold);

	registration::class_<Alpha::ModelComponent>("ModelComponent")
		.property("ObjPath", &Alpha::ModelComponent::GetPath, &Alpha::ModelComponent::SetPath)
		(
			metadata(Alpha::MetadataType::FileType, Alpha::MetadataFileType::Model)
		);

	registration::class_<Alpha::PointLightComponent>("PointLightComponent")
		.property("Light", &Alpha::PointLightComponent::Light)
		(
			policy::prop::bind_as_ptr
		);

	registration::class_<Alpha::Light>("Light")
		.constructor<>()
		.property("Color", &Alpha::Light::Color)
		(
			metadata(Alpha::MetadataType::VectorUsage, Alpha::MetadataVectorUsage::Color)
		)
		.property("Ambient", &Alpha::Light::Ambient)
		.property("Diffuse", &Alpha::Light::Diffuse)
		.property("Specular", &Alpha::Light::Specular)
		.property("ConstantFalloff", &Alpha::Light::ConstantFalloff)
		.property("LinearFalloff", &Alpha::Light::LinearFalloff)
		.property("QuadraticFalloff", &Alpha::Light::QuadraticFalloff);
}

