#pragma once

#include <QString>
#include "BaseEdit.h"

class NamedEdit : public BaseEdit
{
	Q_OBJECT

public:
	NamedEdit(const rttr::instance& instancePtr, const rttr::property& property, QWidget* parent);

	void SetName(const QString& name);

protected:
	QHBoxLayout* horizontalLayout;
	QLabel* label;

private:
	void CreateLayout();
};

