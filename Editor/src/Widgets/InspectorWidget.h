#pragma once

#include <QtWidgets>

#include "rttr/type.h"
#include "Edits/ComponentEdit.h"
#include "ExpandableWidget.h"

namespace Alpha
{
	class Entity;
}

class InspectorWidget : public QWidget
{
	Q_OBJECT

public:
	InspectorWidget(QWidget* parent);

	void SetEntity(Alpha::Entity& entity);

public slots:
	void OnSelectedEntityChanged(Alpha::Entity& selectedEnitity);

private:
	QVBoxLayout* layout;
	Alpha::Entity* selectedEntity;

	QMap<rttr::type, ComponentEdit*> typeToEdit;

	template<typename T>
	void TryShowComponentEdit(Alpha::Entity& entity);
	void HideAllComponents();
};

template<typename T>
void InspectorWidget::TryShowComponentEdit(Alpha::Entity& entity)
{
	if (!entity.HasComponent<T>())
	{
		return;
	}

	T& component = entity.GetComponent<T>();
	rttr::type componentType = rttr::type::get<T>();

	if (!typeToEdit.contains(componentType))
	{
		ComponentEdit* edit = new ComponentEdit(component, componentType, this);
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
