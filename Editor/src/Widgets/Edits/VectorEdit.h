#pragma once

#include "BaseEdit.h"
#include "glm/vec3.hpp"

template<int Components>
class VectorEdit : public BaseEdit
{
public:
	VectorEdit(const rttr::instance& instance, const rttr::property& property, QWidget* parent);

	void Update() override;

private:
	QLineEdit* lines[Components];

private slots:
	void OnLineChanged();
};

template<int T>
struct VectorComponentDispatcher;

template<>
struct VectorComponentDispatcher<3>
{
	using Type = glm::vec3;
};

template<>
struct VectorComponentDispatcher<4>
{
	using Type = glm::vec4;
};

template<int Components>
VectorEdit<Components>::VectorEdit(const rttr::instance& instance, const rttr::property& property, QWidget* parent) : BaseEdit(instance, property, parent)
{
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->setSpacing(3);
	mainLayout->setMargin(1);
	QHBoxLayout* editsLayout = new QHBoxLayout(this);
	editsLayout->setSpacing(3);
	QString names[4]{ "x", "y", "z", "a" };

	QLabel* propertyLabel = new QLabel(this);
	propertyLabel->setText(QString::fromStdString(property.get_name()));
	mainLayout->addWidget(propertyLabel);

	for (int i = 0; i < Components; i++)
	{
		QLabel* label = new QLabel(this);
		label->setText(names[i]);
		editsLayout->addWidget(label);

		lines[i] = new QLineEdit(this);
		lines[i]->setValidator(new QDoubleValidator(lines[i]));
		editsLayout->addWidget(lines[i]);

		connect(lines[i], &QLineEdit::textChanged, this, &VectorEdit::OnLineChanged);
	}

	mainLayout->addLayout(editsLayout);

	setLayout(mainLayout);
	Update();
}

template<int Components>
void VectorEdit<Components>::Update()
{
	VectorComponentDispatcher<Components>::Type value = GetValue<VectorComponentDispatcher<Components>::Type>();

	for (int i = 0; i < Components; i++)
	{
		lines[i]->setText(QString::number(value[i]));
	}
}

template<int Components>
void VectorEdit<Components>::OnLineChanged()
{
	VectorComponentDispatcher<Components>::Type value;

	for (int i = 0; i < Components; i++)
	{
		value[i] = lines[i]->text().toFloat();
	}

	SetValue(value);
}