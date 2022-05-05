#include "ExpandableWidget.h"

ExpandableWidget::ExpandableWidget(const QString& name, QWidget* parent) : QFrame(parent)
{
    innerWidget = nullptr;

    setFrameStyle(QFrame::Box);
    setContentsMargins(1, 2, 1, 2);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    headerLayout = new QHBoxLayout(this);
    headerLayout->setSpacing(15);
    toggleButton = new QToolButton(this);
    toggleButton->setStyleSheet("QToolButton { border: none; }");
    toggleButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    toggleButton->setArrowType(Qt::ArrowType::DownArrow);
    toggleButton->setFixedSize(QSize(30, 25));

    label = new QLabel(this);
    label->setText(name);

    headerLayout->addWidget(toggleButton);
    headerLayout->addWidget(label);
    mainLayout->addLayout(headerLayout);

    horizontalLine = new QFrame(this);
    horizontalLine->setFrameStyle(QFrame::HLine);
    mainLayout->addWidget(horizontalLine);

    setLayout(mainLayout);

    QObject::connect(toggleButton, &QToolButton::clicked, this, &ExpandableWidget::OnCollapseButtonPressed);
}

void ExpandableWidget::SetWidget(QWidget* widget)
{
	if (innerWidget)
	{
		layout()->removeWidget(innerWidget);
	}

	innerWidget = widget;
    layout()->addWidget(innerWidget);
}

void ExpandableWidget::OnCollapseButtonPressed()
{
	bool isVisible = innerWidget->isVisible();
    bool toggledVisibility = !isVisible;

    horizontalLine->setVisible(toggledVisibility);
	innerWidget->setVisible(toggledVisibility);
    toggleButton->setArrowType(toggledVisibility ? Qt::ArrowType::DownArrow : Qt::ArrowType::RightArrow);
}
