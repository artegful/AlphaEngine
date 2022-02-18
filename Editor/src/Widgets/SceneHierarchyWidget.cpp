#include "SceneHierarchyWidget.h"

#include "Models/EntityModel.h"

SceneHierarchyWidget::SceneHierarchyWidget(const QString& title, QWidget* parent) : QDockWidget(title, parent)
{
	treeView = new QTreeView(this);
	setWidget(treeView);
}

void SceneHierarchyWidget::showEvent(QShowEvent* event)
{
	QDockWidget::showEvent(event);

	entityModel = new EntityModel();
	treeView->setModel(entityModel);
	connect(treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &SceneHierarchyWidget::OnSelectionChanged);
}

void SceneHierarchyWidget::OnSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
	QModelIndex selectedIndex = selected.indexes().first();
	Alpha::Entity& selectedEntity = entityModel->GetEntity(selectedIndex);

	emit SelectedEntityChanged(selectedEntity);
}

