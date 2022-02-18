#pragma once

#include <QtWidgets>

class ExpandableWidget : public QFrame
{
public:
	ExpandableWidget(const QString& name, QWidget* parent);
	void SetWidget(QWidget* widget);

private:
	QVBoxLayout *mainLayout;
	QToolButton *toggleButton;
	QLabel* label;
	QWidget *innerWidget;
	QFrame* horizontalLine;

public slots:
	void OnCollapseButtonPressed();
};

