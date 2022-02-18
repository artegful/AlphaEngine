#include "InspectorWidget.h"

#include "Edits/ComponentEdit.h"

#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/CameraComponent.h"
#include "ECS/Entity.h"

InspectorWidget::InspectorWidget(QWidget* parent) : QWidget(parent)
{
	selectedEntity = nullptr;

	layout = new QVBoxLayout(this);
	layout->setAlignment(Qt::AlignTop);

	setLayout(layout);
}

void InspectorWidget::SetEntity(Alpha::Entity& entity)
{
	selectedEntity = &entity;

	HideAllComponents();

	TryShowComponentEdit<Alpha::TransformComponent>(entity);
	TryShowComponentEdit<Alpha::SpriteComponent>(entity);
	TryShowComponentEdit<Alpha::CameraComponent>(entity);

	show();
}

void InspectorWidget::HideAllComponents()
{
	for (auto edit : typeToEdit)
	{
		edit->hide();
	}
}

void InspectorWidget::OnSelectedEntityChanged(Alpha::Entity& selectedEnitity)
{
	SetEntity(selectedEnitity);
}