#pragma once

#include "BaseEdit.h"

class ReflectedItemEdit : public BaseEdit
{
public:
	ReflectedItemEdit(const rttr::instance& instance, const rttr::property& property, QWidget* parent);

	void Update() override;
	void SetInstance(const rttr::instance& instance) override;

private:
	QWidget* innerWidget;
	QVector<BaseEdit*> edits;
};

