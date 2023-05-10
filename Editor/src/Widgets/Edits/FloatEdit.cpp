#include "FloatEdit.h"

#include "StandardEditLayout.h"

FloatEdit::FloatEdit(const rttr::instance& instance, const rttr::property& property, QWidget* parent) : BaseEdit(instance, property, parent)
{
	lineEdit = new QLineEdit(this);
	lineEdit->setValidator(new QRegExpValidator(QRegExp("[+-]?\\d*[\\.,]?\\d+"), this));
	connect(lineEdit, &QLineEdit::textChanged, this, &FloatEdit::OnLineChanged);

	StandardEditLayout *layout = new StandardEditLayout(property, this);
	layout->addWidget(lineEdit);
	layout->ApplyStretch();
	setLayout(layout);

	Update();
}

void FloatEdit::Update()
{
	float value = GetValue<float>();
	lineEdit->setText(QString::number(value));
}

void FloatEdit::OnLineChanged()
{
	float value = lineEdit->text().toFloat();
	SetValue(value);
}