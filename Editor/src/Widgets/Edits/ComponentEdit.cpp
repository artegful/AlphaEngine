#include "ComponentEdit.h"

#include "rttr/property.h"
#include "EditFactory.h"

ComponentEdit::ComponentEdit(const rttr::instance& instancePtr, rttr::type type, QWidget* parent) : ExpandableWidget(QString::fromStdString(type.get_name()), parent)
{
	QWidget* widget = new QWidget(this);
	layout = new QVBoxLayout(this);
	layout->setAlignment(Qt::AlignTop);

	for (auto property : type.get_properties())
	{
		BaseEdit* edit = EditFactory::CreateEdit(instancePtr, property, this);
		edits.push_back(edit);
		layout->addWidget(edit);
	}

	widget->setLayout(layout);
	SetWidget(widget);
}

void ComponentEdit::SetInstance(rttr::variant instancePtr)
{
	for (auto edit : edits)
	{
		edit->SetInstance(instancePtr);
	}
}
