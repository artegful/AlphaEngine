#pragma once

#include <QtWidgets>

namespace Alpha
{
	class Entity;
	class Scene;
}

class EntityModel;

class SceneHierarchyWidget : public QDockWidget
{
	Q_OBJECT

public:
	SceneHierarchyWidget(const QString& title, QWidget* parent);

	void InitScene(Alpha::Scene* scene);
	void SetScene(Alpha::Scene* scene);

private:
	QTreeView* treeView;
	EntityModel* entityModel;


private slots:
	void OnSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
	void OnRightClickEntityDelete();
	void OnRightClickCreateEntity();

signals:
	void SelectedEntityChanged(Alpha::Entity& selectedEntity);
	void SelectionCleared();
};

