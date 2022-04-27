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

void SceneHierarchyWidget::showEvent(QShowEvent* event)
{
	QDockWidget::showEvent(event);

	Alpha::Scene* sceneFromRuntime = Alpha::Engine::Get()->GetGameLayer().GetSceneManager().GetCurrentScene();

	entityModel = new EntityModel(sceneFromRuntime);
	treeView->setModel(entityModel);
	connect(treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &SceneHierarchyWidget::OnSelectionChanged);
}

void SceneHierarchyWidget::OpenScene(const QString& filePath)
{
	Alpha::Scene* scene = new Alpha::Scene();
	Alpha::SceneSerializer serializer(scene);
	serializer.Deserialize(filePath.toStdString());

	SetScene(scene);
}

void SceneHierarchyWidget::SaveScene(const QString& filePath)
{
	Alpha::SceneSerializer serializer(entityModel->GetCurrentScene());
	serializer.Serialize(filePath.toStdString());
}

void SceneHierarchyWidget::CreateNewScene()
{
	Alpha::Scene* scene = new Alpha::Scene();
	SetScene(scene);
}

void SceneHierarchyWidget::SetScene(Alpha::Scene* scene)
{
	treeView->selectionModel()->clearSelection();

	Alpha::Engine::Get()->GetGameLayer().GetSceneManager().ChangeScene(scene);
	entityModel->ChangeScene(scene);
}

void SceneHierarchyWidget::OnRightClickEntityDelete()
{
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