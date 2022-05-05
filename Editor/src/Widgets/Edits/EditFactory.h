#pragma once

#include "BaseEdit.h"

class EditFactory
{
public:
	static BaseEdit* CreateEdit(const rttr::instance& instancePtr, const rttr::property& property, QWidget* parent);
};

