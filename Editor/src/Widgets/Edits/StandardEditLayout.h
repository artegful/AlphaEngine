#pragma once

#include <QtWidgets>
#include "rttr/property.h"

class StandardEditLayout : public QHBoxLayout
{
public:
	StandardEditLayout(const rttr::property& property, QWidget* parent);
	StandardEditLayout(const QString& name, QWidget* parent);

	void ApplyStretch();
};

