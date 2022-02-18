#pragma once

#include <QtWidgets>

namespace Alpha
{
	class Entity;
}

class EntityModel;

class SceneHierarchyWidget : public QDockWidget
{
	Q_OBJECT

public:
	SceneHierarchyWidget(const QString& title, QWidget* parent);

	void showEvent(QShowEvent* event);

private:
	QTreeView* treeView;
	EntityModel* entityModel;

private slots:
	void OnSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

signals:
	void SelectedEntityChanged(Alpha::Entity& selectedEntity);
};

