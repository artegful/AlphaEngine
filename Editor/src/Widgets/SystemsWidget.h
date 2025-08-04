#pragma once

#include <QtWidgets>

namespace Alpha
{
	class Scene;
}

class SystemModel;

class SystemsWidget : public QDockWidget
{
	Q_OBJECT

public:
	SystemsWidget(const QString& title, QWidget* parent);
	void InitScene(Alpha::Scene* scene);
	void SetScene(Alpha::Scene* scene);

private:
	QListView* listView;
	SystemModel* systemModel;

private slots:
	void OnRightClickDelete();
	void OnRightClickCreate();
};

