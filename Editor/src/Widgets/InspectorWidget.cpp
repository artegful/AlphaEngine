#include "InspectorWidget.h"

#include "Edits/ComponentEdit.h"

#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/OrthoCameraComponent.h"
#include "Components/Rigidbody2DComponent.h"
#include "Components/Box2DColliderComponent.h"
#include "ECS/Entity.h"
#include <Components/ModelComponent.h>

InspectorWidget::InspectorWidget(QWidget* parent) : QWidget(parent)
{
	selectedEntity = nullptr;

	layout = new QVBoxLayout(this);
	QMenu* buttonMenu = new QMenu(this);

	QAction* addSpriteComponent = new QAction(tr("Sprite Component"));
	connect(addSpriteComponent, &QAction::triggered, this, &InspectorWidget::OnAddSpriteComponent);

	QAction* addCameraComponent = new QAction(tr("OrthoCamera Component"));
	connect(addCameraComponent, &QAction::triggered, this, &InspectorWidget::OnAddCameraComponent);

	QAction* addRigidbody2DComponent = new QAction(tr("Rigidbody 2D"));
	connect(addRigidbody2DComponent, &QAction::triggered, this, &InspectorWidget::OnAddRidigbody2DComponent);

	QAction* addBox2DColliderComponent = new QAction(tr("2D Box Collider Component"));
	connect(addBox2DColliderComponent, &QAction::triggered, this, &InspectorWidget::OnAddBox2DColliderComponent);

	QAction* addModelComponent = new QAction(tr("Model Component"));
	connect(addModelComponent, &QAction::triggered, this, &InspectorWidget::OnAddModelComponent);

	buttonMenu->addAction(addSpriteComponent);
	buttonMenu->addAction(addCameraComponent);
	buttonMenu->addAction(addRigidbody2DComponent);
	buttonMenu->addAction(addBox2DColliderComponent);
	buttonMenu->addAction(addModelComponent);

	addComponentButton = new QToolButton(this);
	addComponentButton->setPopupMode(QToolButton::MenuButtonPopup);
	addComponentButton->setMenu(buttonMenu);
	addComponentButton->setDefaultAction(new QAction(tr("Add Component")));

	layout->setAlignment(Qt::AlignTop);
	layout->addWidget(addComponentButton);

	setLayout(layout);
}

void InspectorWidget::SetEntity(Alpha::Entity& entity)
{
	selectedEntity = &entity;

	Reset();
}

void InspectorWidget::OnSelectionCleared()
{
	hide();
}

void InspectorWidget::Reset()
{
	HideAllComponents();

	TryShowComponentEdit<Alpha::TransformComponent>();
	TryShowComponentEdit<Alpha::SpriteComponent>();
	TryShowComponentEdit<Alpha::OrthoCameraComponent>();
	TryShowComponentEdit<Alpha::Rigidbody2DComponent>();
	TryShowComponentEdit<Alpha::Box2DColliderComponent>();
	TryShowComponentEdit<Alpha::ModelComponent>();

	show();
}

void InspectorWidget::HideAllComponents()
{
	for (auto edit : typeToEdit)
	{
		edit->hide();
	}
}

void InspectorWidget::OnAddSpriteComponent()
{
	TryAddComponent<Alpha::SpriteComponent>();
}

void InspectorWidget::OnAddCameraComponent()
{
	TryAddComponent<Alpha::OrthoCameraComponent>();
}

void InspectorWidget::OnAddRidigbody2DComponent()
{
	TryAddComponent<Alpha::Rigidbody2DComponent>();
}

void InspectorWidget::OnAddBox2DColliderComponent()
{
	TryAddComponent<Alpha::Box2DColliderComponent>();
}

void InspectorWidget::OnAddModelComponent()
{
	TryAddComponent<Alpha::ModelComponent>();

	if (selectedEntity->HasComponent<Alpha::ModelComponent>())
	{
		auto& component = selectedEntity->GetComponent<Alpha::ModelComponent>();

		static std::string defaultModel = "assets/models/defaultCube/cube.obj";
		if (std::filesystem::exists(defaultModel))
		{
			component.SetPath(defaultModel);
		}
	}
}

void InspectorWidget::OnSelectedEntityChanged(Alpha::Entity& selectedEnitity)
{
	SetEntity(selectedEnitity);
}

void InspectorWidget::OnDeleteButtonPressed(rttr::type componentType)
{
	TryDeleteComponent<Alpha::SpriteComponent>(componentType);
	TryDeleteComponent<Alpha::OrthoCameraComponent>(componentType);
	TryDeleteComponent<Alpha::Rigidbody2DComponent>(componentType);
	TryDeleteComponent<Alpha::Box2DColliderComponent>(componentType);
	TryDeleteComponent<Alpha::ModelComponent>(componentType);
}
