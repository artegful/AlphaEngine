#pragma once

#include <QtWidgets>
#include "rttr/type.h"
#include "rttr/instance.h"

#include "Widgets/ExpandableWidget.h"
#include "BaseEdit.h"

class ComponentEdit : public ExpandableWidget
{
	Q_OBJECT

public:
	ComponentEdit(const rttr::instance& instancePtr, rttr::type type, QWidget* parent);
	void SetInstance(rttr::variant instancePtr);

signals:
	void DeleteButtonPressed(rttr::type componentType);

private:
	QVector<BaseEdit*> edits;
	QVBoxLayout* layout;
	rttr::type* componentType;

	QToolButton* deleteButton;

private slots:
	void OnDeleteButtonPressed();
};

