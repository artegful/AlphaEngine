#pragma once

#include <QtWidgets>

#include "rttr/type.h"
#include "ECS/Entity.h"
#include "Edits/ComponentEdit.h"
#include "ExpandableWidget.h"

class InspectorWidget : public QWidget
{
	Q_OBJECT

public:
	InspectorWidget(QWidget* parent);

	void SetEntity(Alpha::Entity& entity);

public slots:
	void OnSelectedEntityChanged(Alpha::Entity& selectedEnitity);
	void OnSelectionCleared();

private:
	QVBoxLayout* layout;
	Alpha::Entity* selectedEntity;
	QToolButton* addComponentButton;

	QMap<rttr::type, ComponentEdit*> typeToEdit;

	template<typename T>
	void TryShowComponentEdit();

	template<typename T>
	void TryDeleteComponent(rttr::type componentType);

	template<typename T, typename... Args>
	void TryAddComponent(Args&&... args);

	void Reset();
	void HideAllComponents();

private slots:
	void OnDeleteButtonPressed(rttr::type componentType);

	void OnAddSpriteComponent();
	void OnAddCameraComponent();
	void OnAddRidigbody2DComponent();
	void OnAddBox2DColliderComponent();
	void OnAddModelComponent();
	void OnAddPointLightComponent();
};

template<typename T>
void InspectorWidget::TryShowComponentEdit()
{
	if (!selectedEntity->HasComponent<T>())
	{
		return;
	}

	T& component = selectedEntity->GetComponent<T>();
	rttr::type componentType = rttr::type::get<T>();

	if (!typeToEdit.contains(componentType))
	{
		ComponentEdit* edit = new ComponentEdit(component, componentType, this);
		connect(edit, &ComponentEdit::DeleteButtonPressed, this, &InspectorWidget::OnDeleteButtonPressed);
		typeToEdit[componentType] = edit;
		layout->addWidget(edit);
	}
	else
	{
		ComponentEdit* edit = typeToEdit[componentType];

		edit->SetInstance(&component);
		edit->show();
	}
}

template<typename T>
void InspectorWidget::TryDeleteComponent(rttr::type componentType)
{
	if (rttr::type::get<T>() == componentType)
	{
		selectedEntity->RemoveComponent<T>();

		Reset();
	}
}

template<typename T, typename... Args>
void InspectorWidget::TryAddComponent(Args&&... args)
{
	if (!selectedEntity->HasComponent<T>())
	{
		selectedEntity->AddComponent<T>(std::forward<Args>(args)...);

		Reset();
	}
}
