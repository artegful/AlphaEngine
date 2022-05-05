#include "BaseEdit.h"

BaseEdit::BaseEdit(const rttr::instance& instance, const rttr::property& property, QWidget* parent) : property(property), instancePtr(instance)
{
	setParent(parent);
}

void BaseEdit::SetInstance(const rttr::instance& instance)
{
	memcpy(&instancePtr, &instance, sizeof(instancePtr));

	Update();
}
