#include "SceneHierarchyWidget.h"

#include <memory>

#include "Core/Engine.h"
#include "ECS/Entity.h"
#include "Scene/Scene.h"
#include "Layers/GameLayer.h"
#include "Scene/SceneManager.h"
#include "Components/NameComponent.h"
#include "Scene/SceneSerializer.h"
#include "Models/EntityModel.h"
#include "Scene/SceneSerializer.h"

SceneHierarchyWidget::SceneHierarchyWidget(const QString& title, QWidget* parent) : QDockWidget(title, parent)
{
	treeView = new QTreeView(this);
	treeView->setContextMenuPolicy(Qt::ActionsContextMenu);
	treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);

	QAction* deleteEntityAction = new QAction(tr("Delete"));
	connect(deleteEntityAction, &QAction::triggered, this, &SceneHierarchyWidget::OnRightClickEntityDelete);
	treeView->addAction(deleteEntityAction);

	QAction* createEntityAction = new QAction(tr("Create Empty"));
	connect(createEntityAction, &QAction::triggered, this, &SceneHierarchyWidget::OnRightClickCreateEntity);
	treeView->addAction(createEntityAction);

	setWidget(treeView);
}

void SceneHierarchyWidget::InitScene(Alpha::Scene* scene)
{
	entityModel = new EntityModel(scene);
	treeView->setModel(entityModel);
	connect(treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &SceneHierarchyWidget::OnSelectionChanged);
}

void SceneHierarchyWidget::SetScene(Alpha::Scene* scene)
{
	treeView->selectionModel()->clearSelection();

	entityModel->ChangeScene(scene);
}

void SceneHierarchyWidget::OnRightClickEntityDelete()
{
	if (!treeView->selectionModel() || !treeView->selectionModel()->hasSelection())
	{
		return;
	}

	QModelIndexList indexes = treeView->selectionModel()->selectedIndexes();

	if (!treeView->selectionModel()->hasSelection())
	{
		return;
	}
	
	entityModel->Remove(indexes);
}

void SceneHierarchyWidget::OnRightClickCreateEntity()
{
	entityModel->Create();
}

void SceneHierarchyWidget::OnSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
	if (!selected.indexes().isEmpty())
	{
		QModelIndex selectedIndex = selected.indexes().first();
		Alpha::Entity& selectedEntity = entityModel->GetEntity(selectedIndex);

		emit SelectedEntityChanged(selectedEntity);
	}
	else
	{
		emit SelectionCleared();
	}
}