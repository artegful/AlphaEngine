#pragma once

#include "BaseEdit.h"

class StringEdit : public BaseEdit
{
public:
	StringEdit(const rttr::instance& instance, const rttr::property& property, QWidget* parent);
	void Update() override;
	void HandleButton();

private:
	QLineEdit* lineEdit;

private slots:
	void OnLineChanged();
};

