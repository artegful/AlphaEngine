#pragma once

#include <QtWidgets>

class ExpanderLayout : public QVBoxLayout
{
public:
	ExpanderLayout(const QString& name, QWidget* parent);
	void SetContentWidget(QWidget* widget);

private:
	QToolButton* toggleButton;
	QLabel* label;
	QWidget* innerWidget;

private:
	void OnCollapseButtonPressed();
};

