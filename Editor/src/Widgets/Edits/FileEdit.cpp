#include "FileEdit.h"

#include "StandardEditLayout.h"

FileEdit::FileEdit(const rttr::instance& instance, const rttr::property& property, const char* fileTypes, QWidget* parent) : BaseEdit(instance, property, parent)
{
	this->fileTypes = fileTypes;

	lineEdit = new QLineEdit(this);
	connect(lineEdit, &QLineEdit::textChanged, this, &FileEdit::OnLineChanged);

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->setSpacing(3);
	mainLayout->setMargin(1);
	QHBoxLayout* editsLayout = new QHBoxLayout(this);
	editsLayout->setSpacing(3);

	QLabel* propertyLabel = new QLabel(this);
	propertyLabel->setText(QString::fromStdString(property.get_name()));
	mainLayout->addWidget(propertyLabel);

	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(lineEdit, 3);

	QPushButton* selectFileButton = new QPushButton(this);
	selectFileButton->setText(tr("open"));
	connect(selectFileButton, &QPushButton::pressed, this, &FileEdit::HandleButton);

	layout->addWidget(selectFileButton, 1);
	mainLayout->addLayout(layout);
	setLayout(mainLayout);

	Update();
}

void FileEdit::Update()
{
	std::string value = GetValue<std::string>();
	lineEdit->setText(QString::fromStdString(value));
}

void FileEdit::HandleButton()
{
	QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"),
		tr("assets"), fileTypes);

	if (!filePath.isEmpty())
	{
		lineEdit->setText(filePath);
	}
}

void FileEdit::OnLineChanged()
{
	std::string value = lineEdit->text().toStdString();
	SetValue(value);
}