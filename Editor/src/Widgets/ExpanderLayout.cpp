#include "ExpanderLayout.h"

ExpanderLayout::ExpanderLayout(const QString& name, QWidget* parent) : QVBoxLayout(parent)
{
    innerWidget = nullptr;
    setSpacing(0);

    QHBoxLayout* headerLayout = new QHBoxLayout(parent);
    headerLayout->setSpacing(15);
    toggleButton = new QToolButton(parent);
    toggleButton->setStyleSheet("QToolButton { border: none; }");
    toggleButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    toggleButton->setArrowType(Qt::ArrowType::DownArrow);
    toggleButton->setFixedSize(QSize(25, 20));

    label = new QLabel(parent);
    label->setText(name);

    headerLayout->addWidget(toggleButton);
    headerLayout->addWidget(label);
    addLayout(headerLayout);

    QObject::connect(toggleButton, &QToolButton::clicked, this, &ExpanderLayout::OnCollapseButtonPressed);
}

void ExpanderLayout::SetContentWidget(QWidget* widget)
{
    if (innerWidget)
    {
        layout()->removeWidget(innerWidget);
    }

    innerWidget = widget;
    layout()->addWidget(innerWidget);
}

void ExpanderLayout::OnCollapseButtonPressed()
{
    bool isVisible = innerWidget->isVisible();
    bool toggledVisibility = !isVisible;

    innerWidget->setVisible(toggledVisibility);
    toggleButton->setArrowType(toggledVisibility ? Qt::ArrowType::DownArrow : Qt::ArrowType::RightArrow);
}
