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

	void showEvent(QShowEvent* event);
	void OpenScene(const QString& filePath);
	void SaveScene(const QString& filePath);
	void CreateNewScene();

private:
	QTreeView* treeView;
	EntityModel* entityModel;

	void SetScene(Alpha::Scene* scene);

private slots:
	void OnSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
	void OnRightClickEntityDelete();
	void OnRightClickCreateEntity();

signals:
	void SelectedEntityChanged(Alpha::Entity& selectedEntity);
	void SelectionCleared();
};

