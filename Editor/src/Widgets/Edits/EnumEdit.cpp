#include "EnumEdit.h"

#include "rttr/enumeration.h"
#include "StandardEditLayout.h"

EnumEdit::EnumEdit(const rttr::instance& instance, const rttr::property& property, QWidget* parent) : BaseEdit(instance, property, parent)
{
	comboBox = new QComboBox(this);
	StandardEditLayout* layout = new StandardEditLayout(property, this);
	layout->addWidget(comboBox);

	rttr::enumeration enumeration = property.get_enumeration();
	values = enumeration.get_values();

	for (auto name : enumeration.get_names())
	{
		comboBox->addItem(QString::fromStdString(name));
	}

	connect(comboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &EnumEdit::OnIndexChanged);

	setLayout(layout);
	Update();
}

void EnumEdit::Update()
{
	comboBox->setCurrentIndex(GetValue<int>());
}

void EnumEdit::OnIndexChanged(int index)
{
	SetValue(values[index]);
}