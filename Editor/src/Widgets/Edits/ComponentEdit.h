#pragma once

#include <QtWidgets>
#include "rttr/type.h"
#include "rttr/instance.h"

#include "Widgets/ExpandableWidget.h"
#include "BaseEdit.h"

class ComponentEdit : public ExpandableWidget
{
public:
	ComponentEdit(const rttr::instance& instancePtr, rttr::type type, QWidget* parent);
	void SetInstance(rttr::variant instancePtr);

private:
	QVector<BaseEdit*> edits;
	QVBoxLayout* layout;
};

