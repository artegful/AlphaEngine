#pragma once

#include "BaseEdit.h"
#include "rttr/variant.h"

namespace rttr
{
	class enumeration;
}

class EnumEdit : public BaseEdit
{
	Q_OBJECT

public:
	EnumEdit(const rttr::instance& instance, const rttr::property& property, QWidget* parent);

	void Update() override;

private:
	QComboBox* comboBox;
	std::vector<rttr::variant> values;

	void OnIndexChanged(int state);
};

