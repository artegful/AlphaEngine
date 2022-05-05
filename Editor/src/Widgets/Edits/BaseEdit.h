#pragma once

#include <QtWidgets>

#include "Components/TransformComponent.h"

#include "rttr/type.h"
#include "rttr/property.h"
#include "rttr/instance.h"

class BaseEdit : public QWidget
{
	Q_OBJECT

public:
	BaseEdit(const rttr::instance& instance, const rttr::property& property, QWidget* parent);
	
	virtual void SetInstance(const rttr::instance& instance);
	virtual void Update() = 0;

	template<typename T>
	void SetValue(T value)
	{
		property.set_value(instancePtr, value);
	}

	template<typename T>
	T GetValue() const
	{
		rttr::variant result = property.get_value(instancePtr);

		return result.convert<T>();
	}

	rttr::variant GetValue() const
	{
		return property.get_value(instancePtr);
	}

protected:
	rttr::instance instancePtr;
	rttr::property property;
};