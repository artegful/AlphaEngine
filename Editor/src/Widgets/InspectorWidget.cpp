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
	QMenu* buttonMenu = new QMenu(this);

	QAction* addSpriteComponent = new QAction(tr("Sprite Component"));
	connect(addSpriteComponent, &QAction::triggered, this, &InspectorWidget::OnAddSpriteComponent);

	QAction* addCameraComponent = new QAction(tr("Camera Component"));
	connect(addCameraComponent, &QAction::triggered, this, &InspectorWidget::OnAddCameraComponent);

	buttonMenu->addAction(addSpriteComponent);
	buttonMenu->addAction(addCameraComponent);

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
	TryShowComponentEdit<Alpha::CameraComponent>();

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
	TryAddComponent<Alpha::CameraComponent>();
}

void InspectorWidget::OnSelectedEntityChanged(Alpha::Entity& selectedEnitity)
{
	SetEntity(selectedEnitity);
}

void InspectorWidget::OnDeleteButtonPressed(rttr::type componentType)
{
	TryDeleteComponent<Alpha::TransformComponent>(componentType);
	TryDeleteComponent<Alpha::SpriteComponent>(componentType);
	TryDeleteComponent<Alpha::CameraComponent>(componentType);
}
