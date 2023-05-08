#include "StringEdit.h"

#include "StandardEditLayout.h"

StringEdit::StringEdit(const rttr::instance& instance, const rttr::property& property, QWidget* parent) : BaseEdit(instance, property, parent)
{
	lineEdit = new QLineEdit(this);
	connect(lineEdit, &QLineEdit::textChanged, this, &StringEdit::OnLineChanged);

	StandardEditLayout* layout = new StandardEditLayout(property, this);
	layout->addWidget(lineEdit);

	QPushButton* selectFileButton = new QPushButton(this);
	selectFileButton->setText(tr("open"));
	connect(selectFileButton, &QPushButton::pressed, this, &StringEdit::HandleButton);

	layout->ApplyStretch();
	setLayout(layout);

	Update();
}

void StringEdit::Update()
{
	std::string value = GetValue<std::string>();
	lineEdit->setText(QString::fromStdString(value));
}

void StringEdit::HandleButton()
{
	QString filePath = QFileDialog::getOpenFileName(this, tr("Open Model"),
		tr("assets"), "Models (*.obj; *.fbx)");

	if (!filePath.isEmpty())
	{
		lineEdit->setText(filePath);
	}
}

void StringEdit::OnLineChanged()
{
	std::string value = lineEdit->text().toStdString();
	SetValue(value);
}