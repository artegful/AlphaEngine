#pragma once

#include "BaseEdit.h"

class FileEdit : public BaseEdit
{
public:
	FileEdit(const rttr::instance& instance, const rttr::property& property, const char* fileTypes, QWidget* parent);
	void Update() override;
	void HandleButton();

private:
	QLineEdit* lineEdit;
	const char* fileTypes;

private slots:
	void OnLineChanged();
};

