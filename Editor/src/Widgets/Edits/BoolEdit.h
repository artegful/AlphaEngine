#pragma once

#include "NamedEdit.h"

class BoolEdit : public BaseEdit
{
	Q_OBJECT

public:
	BoolEdit(const rttr::instance& instance, const rttr::property& property, QWidget* parent);

	void Update() override;

private:
	QCheckBox* checkBox;

	void OnStateChanged(int state);
};

