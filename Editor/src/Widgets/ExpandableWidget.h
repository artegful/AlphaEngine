#pragma once

#include <QtWidgets>

class ExpandableWidget : public QFrame
{
public:
	ExpandableWidget(const QString& name, QWidget* parent);
	void SetWidget(QWidget* widget);

private:
	QToolButton *toggleButton;
	QLabel* label;
	QWidget *innerWidget;
	QFrame* horizontalLine;

protected:
	QVBoxLayout* mainLayout;
	QHBoxLayout* headerLayout;

public slots:
	void OnCollapseButtonPressed();

	friend class ComponentEdit;
};

