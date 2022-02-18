#include "StandardEditLayout.h"

StandardEditLayout::StandardEditLayout(const rttr::property& property, QWidget* parent) : StandardEditLayout(QString::fromStdString(property.get_name()), parent)
{ }

StandardEditLayout::StandardEditLayout(const QString& name, QWidget* parent) : QHBoxLayout(parent)
{
	setMargin(1);
	QLabel* label = new QLabel(parent);
	label->setText(name);
	addWidget(label);
}

void StandardEditLayout::ApplyStretch()
{
	if (count() <= 1)
	{
		return;
	}

	setStretch(0, 1);

	int amountOfOtherElements = count() - 1;
	float stretchForOtherElements = 2;
	float stretch = stretchForOtherElements / amountOfOtherElements;

	for (int i = 1; i < count(); i++)
	{
		setStretch(i, stretch);
	}
}
