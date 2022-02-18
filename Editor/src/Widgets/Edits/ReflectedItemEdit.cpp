#include "ReflectedItemEdit.h"

#include "Widgets/ExpanderLayout.h"
#include "EditFactory.h"

ReflectedItemEdit::ReflectedItemEdit(const rttr::instance& instance, const rttr::property& property, QWidget* parent) : BaseEdit(instance, property, parent)
{
	rttr::variant propertyVariant = GetValue();
	Q_ASSERT(propertyVariant.get_type().is_pointer());

	ExpanderLayout* mainLayout = new ExpanderLayout(QString::fromStdString(property.get_name()), this);
	mainLayout->setMargin(0);
	QVBoxLayout* innerLayout = new QVBoxLayout(this);
	innerLayout->setSpacing(4);
	innerWidget = new QWidget(this);
	innerWidget->setLayout(innerLayout);

	for (auto innerProperty : propertyVariant.get_type().get_properties())
	{
		BaseEdit* innerEdit = EditFactory::CreateEdit(propertyVariant, innerProperty, this);
		edits.push_back(innerEdit);
		innerLayout->addWidget(innerEdit);
	}

	mainLayout->SetContentWidget(innerWidget);
	setLayout(mainLayout);
}

void ReflectedItemEdit::Update()
{
	for (auto edit : edits)
	{
		edit->Update();
	}
}

void ReflectedItemEdit::SetInstance(const rttr::instance& instance)
{
	memcpy(&instancePtr, &instance, sizeof(instancePtr));
	rttr::variant propertyVariant = GetValue();

	for (auto edit : edits)
	{
		edit->SetInstance(propertyVariant);
	}
}
