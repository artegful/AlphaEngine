#include "BoolEdit.h"

#include "StandardEditLayout.h"

BoolEdit::BoolEdit(const rttr::instance& instance, const rttr::property& property, QWidget* parent) : BaseEdit(instance, property, parent)
{
	checkBox = new QCheckBox(this);
	StandardEditLayout* layout = new StandardEditLayout(property, this);
	layout->addWidget(checkBox);

	connect(checkBox, &QCheckBox::stateChanged, this, &BoolEdit::OnStateChanged);

	setLayout(layout);
	Update();
}

void BoolEdit::Update()
{
	checkBox->setCheckState(GetValue<bool>() ? Qt::Checked : Qt::Unchecked);
}

void BoolEdit::OnStateChanged(int state)
{
	Qt::CheckState parsedState = static_cast<Qt::CheckState>(state);
	SetValue(parsedState == Qt::Checked ? true : false);
}