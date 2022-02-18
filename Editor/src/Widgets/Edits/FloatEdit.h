#pragma once

#include "BaseEdit.h"

class FloatEdit : public BaseEdit
{
public:
	FloatEdit(const rttr::instance& instance, const rttr::property& property, QWidget* parent);
	void Update() override;

private:
	QLineEdit* lineEdit;

private slots:
	void OnLineChanged();
};

