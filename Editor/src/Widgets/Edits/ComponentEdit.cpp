#include "ComponentEdit.h"

#include "rttr/property.h"
#include "EditFactory.h"
#include "Reflection/MetadataType.h"

ComponentEdit::ComponentEdit(const rttr::instance& instancePtr, rttr::type type, QWidget* parent) : ExpandableWidget(QString::fromStdString(type.get_name()), parent)
{
	rttr::variant isNecessary = type.get_metadata(Alpha::MetadataType::ComponentNecessity).to_bool();

	if (!isNecessary.is_valid() || !isNecessary.to_bool())
	{
		deleteButton = new QToolButton(this);
		deleteButton->setText(tr("x"));
		deleteButton->setStyleSheet("QToolButton { border: none; }");
		headerLayout->addWidget(deleteButton);
		connect(deleteButton, &QToolButton::clicked, this, &ComponentEdit::OnDeleteButtonPressed);
	}

	QWidget* widget = new QWidget(this);
	layout = new QVBoxLayout(this);
	layout->setAlignment(Qt::AlignTop);

	componentType = new rttr::type(type);

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

void ComponentEdit::OnDeleteButtonPressed()
{
	emit DeleteButtonPressed(*componentType);
}
